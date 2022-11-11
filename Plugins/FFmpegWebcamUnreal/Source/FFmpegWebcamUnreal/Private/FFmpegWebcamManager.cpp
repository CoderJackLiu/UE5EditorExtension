// Fill out your copyright notice in the Description page of Project Settings.

#include "FFmpegWebcamManager.h"
#include "PsyMocapSDK.h"
#include "Async/Async.h"
#include "FFmpegWebcamUnreal.h"
#include "Engine/Canvas.h"
#include "Misc/MessageDialog.h"
#include <thread>
#include <string>
#include <chrono> 
#include <iostream>

#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"


void AFFmpegWebcamManagerDaemon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// avcodec_close(pCodecContext);
	// avformat_close_input(&pFormatContext);
}

void UFFmpegWebcamManager::SetCamera(FString name)
{
	cameraName = name;
}

void UFFmpegWebcamManager::OpenCamera(bool& status)
{
	status = false;
	Pointer = UTexture2D::CreateTransient(videoSize.X, videoSize.Y, PF_B8G8R8A8);
	Pointer->UpdateResource();
	Region = new FUpdateTextureRegion2D(0, 0, 0, 0, Pointer->GetSizeX(), Pointer->GetSizeY());

	avdevice_register_all();
	pFormatContext = avformat_alloc_context();
	const AVInputFormat* ifmt = av_find_input_format(PLATFORM_WINDOWS ? "dshow" : PLATFORM_MAC ? "avfoundation" : "");

	AVDictionary* options = nullptr;
	av_dict_set(&options, "video_size", TCHAR_TO_ANSI(*(FString::FromInt(videoSize.X) + "x" + FString::FromInt(videoSize.Y))), 0);
	av_dict_set(&options, "framerate", TCHAR_TO_ANSI(*(FString::FromInt(frameRate))), 0);

	FString cameraURL = PLATFORM_WINDOWS ? "video=" + cameraName : PLATFORM_MAC ? FString::FromInt(cameraIndex) : "";

	if (avformat_open_input(&pFormatContext, TCHAR_TO_ANSI(*cameraURL), ifmt, &options) != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Open Camera"));
		return;
	}

	if (avformat_find_stream_info(pFormatContext, nullptr) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot find any stream"));
		return;
	}

	videoStream = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Find %d Stream"), pFormatContext->nb_streams);

	for (uint8 i = 0; i < pFormatContext->nb_streams; i++) {
		if (pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = pFormatContext->streams[i];
			break;
		}
	}

	if (videoStream == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot find any video stream"));
		return;
	}

	pCodec = avcodec_find_decoder(videoStream->codecpar->codec_id);
	if (pCodec == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Find Any Decoder"));
		return;
	}

	pCodecContext = avcodec_alloc_context3(pCodec);
	avcodec_parameters_to_context(pCodecContext, videoStream->codecpar);

	if (avcodec_open2(pCodecContext, pCodec, nullptr) != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Open Decoder"));
		return;
	}

	videoSize.X = pCodecContext->width;
	videoSize.Y = pCodecContext->height;

	packet = av_packet_alloc();
	frame = av_frame_alloc();
	frame_bgra = av_frame_alloc();
	frame_rgb = av_frame_alloc();

	imageBufferBRGA.Init(0,videoSize.X * videoSize.Y);

	ImageBufferRGB.resize(videoSize.X * videoSize.Y * 3);

	av_image_fill_arrays(frame_bgra->data, frame_bgra->linesize, (uint8_t*)imageBufferBRGA.GetData(), AV_PIX_FMT_BGRA, videoSize.X, videoSize.Y, 1);
	frame_bgra->format = AV_PIX_FMT_BGRA;

	av_image_fill_arrays(frame_rgb->data, frame_rgb->linesize, ImageBufferRGB.data(), AV_PIX_FMT_RGB24, videoSize.X, videoSize.Y, 1);
	frame_rgb->format = AV_PIX_FMT_RGB24;

	swsContext_bgra = sws_getContext(videoSize.X, videoSize.Y, pCodecContext->pix_fmt,
		videoSize.X, videoSize.Y, AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);

	if (swsContext_bgra == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Get swsContent_brga"));
		return;
	}

	swsContext_rgb = sws_getContext(videoSize.X, videoSize.Y, pCodecContext->pix_fmt,
		videoSize.X, videoSize.Y, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

	if (swsContext_rgb == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Get swsContent_rgb"));
		return;
	}
	status = true;

	daemonActor = (AFFmpegWebcamManagerDaemon*)GWorld->SpawnActor(AFFmpegWebcamManagerDaemon::StaticClass());
	daemonActor->pFormatContext = pFormatContext;
	daemonActor->pCodecContext = pCodecContext;

	//todo liuqi
	// TextureBuffer=	UTexture2D::CreateTransient(videoSize.X, videoSize.Y, PF_B8G8R8A8);
	//
	// P_Mat=LoadObject<UMaterialInterface>(this,TEXT("/Game/Test/TestMat.TestMat"));
	//
	// if (P_Mat)
	// {
	// 	DynamicMaterial=UKismetMaterialLibrary::CreateDynamicMaterialInstance(this,P_Mat);
	// 	DynamicMaterial->SetTextureParameterValue(TEXT("Texture"),TextureBuffer);
	// }
	Start();
}

void UFFmpegWebcamManager::CloseCamera()
{
	Stop();
	if (Thread != nullptr)
	{
		Thread->WaitForCompletion();
		delete Thread;
		Thread = nullptr;
	}
	if (CheckValid())
	{
		daemonActor->Destroy();
		daemonActor = nullptr;
	}

	if(Pointer)
	{
		Pointer->ReleaseResource();
	}
}

void UFFmpegWebcamManager::ReadFrame(bool& status)
{
	status = false;
	if (!CheckValid())return;

	av_packet_unref(packet);
	if (av_read_frame(pFormatContext, packet) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Read Frame"));
		return;
	}
	int ret = avcodec_send_packet(pCodecContext, packet);
	if (ret != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Decode Packet"));
		return;
	}
	if (avcodec_receive_frame(pCodecContext, frame) >= 0) {
		sws_scale(swsContext_bgra, (const uint8_t* const*)frame->data, frame->linesize, 0, videoSize.Y, frame_bgra->data, frame_bgra->linesize);
		sws_scale(swsContext_rgb, (const uint8_t* const*)frame->data, frame->linesize, 0, videoSize.Y, frame_rgb->data, frame_rgb->linesize);
		status = true;
	}
}

void UFFmpegWebcamManager::DrawToCanvas(UCanvas* canvas)
{
	if (!CheckValid())return;
	Pointer->UpdateTextureRegions(0, 1, Region, 4 * Pointer->GetSizeX(), 4, (uint8*)imageBufferBRGA.GetData());
	canvas->K2_DrawTexture(Pointer, FVector2D(0, 0), FVector2D(canvas->SizeX, canvas->SizeY), FVector2D(0, 0));
}

void UFFmpegWebcamManager::DrawToRT(UTextureRenderTarget2D* TargetRT)
{
	// UTexture2D* Pointer = UTexture2D::CreateTransient(videoSize.X, videoSize.Y, PF_B8G8R8A8);
	// uint8* MipData = static_cast<uint8*>(TextureBuffer->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	// FMemory::Memcpy(MipData, imageBufferBRGA.GetData(), videoSize.X * videoSize.Y);
	// TextureBuffer->GetPlatformData()->Mips[0].BulkData.Unlock();
	// TextureBuffer->UpdateResource();
	// // TextureBuffer
	// if (DynamicMaterial)
	// {
	// 	UKismetRenderingLibrary::DrawMaterialToRenderTarget(this,TargetRT,DynamicMaterial);
	// }
}

void UFFmpegWebcamManager::GetCameraList(TArray<FString>& list)
{
	list.Empty();
	avdevice_register_all();
	AVFormatContext* pFmtCtx = avformat_alloc_context();
	const AVInputFormat* ifmt = av_find_input_format(PLATFORM_WINDOWS ? "dshow" : PLATFORM_MAC ? "avfoundation" : "");

	AVDictionary* options = nullptr;
	av_dict_set(&options, "list_devices", "true", 0);

	FFMPEG_LogArray.Empty();
	FFMPEG_IsSaveToArray = true;
	avformat_open_input(&pFmtCtx, nullptr, ifmt, &options);
	FFMPEG_IsSaveToArray = false;
	avformat_close_input(&pFmtCtx);

	for (int i = 0; i < FFMPEG_LogArray.Num(); i++)
	{
#if PLATFORM_WINDOWS
		if (FFMPEG_LogArray[i].Find("DirectShow audio devices") != INDEX_NONE)break;
		if (i == FFMPEG_LogArray.Num() - 1)break;
		if (FFMPEG_LogArray[i].Find("Alternative name") != INDEX_NONE)
		{
			if (i - 4 < 0)
				break;
			if (FFMPEG_LogArray[i - 3].Find("video") != INDEX_NONE) {
				int32 b = FFMPEG_LogArray[i - 4].Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromStart);
				int32 e = FFMPEG_LogArray[i - 4].Find("\"", ESearchCase::IgnoreCase, ESearchDir::FromEnd);
				list.Add(FFMPEG_LogArray[i - 4].Mid(b + 1, e - b - 1));
			}
		}
#elif PLATFORM_MAC
		if (FFMPEG_LogArray[i].Find("AVFoundation audio devices") != INDEX_NONE)break;
		if (FFMPEG_LogArray[i].Find("] ") != INDEX_NONE)
		{
			int32 b = FFMPEG_LogArray[i].Find("] ", ESearchCase::IgnoreCase, ESearchDir::FromStart);
			list.Add(FFMPEG_LogArray[i].Mid(b + 2, FFMPEG_LogArray[i].Len() - b - 3));
		}
#endif
	}
	FFMPEG_LogArray.Empty();
}

bool UFFmpegWebcamManager::CheckCameraAvailable(FString& log)
{
	log.Empty();
	avdevice_register_all();
	AVFormatContext* pFmtCtx = avformat_alloc_context();
	const AVInputFormat* ifmt = av_find_input_format(PLATFORM_WINDOWS ? "dshow" : PLATFORM_MAC ? "avfoundation" : "");

	AVDictionary* options = nullptr;
	av_dict_set(&options, "video_size", TCHAR_TO_ANSI(*(FString::FromInt(videoSize.X) + "x" + FString::FromInt(videoSize.Y))), 0);
	av_dict_set(&options, "framerate", TCHAR_TO_ANSI(*(FString::FromInt(frameRate))), 0);

	FString cameraURL = PLATFORM_WINDOWS ? "video=" + cameraName : PLATFORM_MAC ? FString::FromInt(cameraIndex) : "";

	FFMPEG_LogArray.Empty();
	FFMPEG_IsSaveToArray = true;
	int result = avformat_open_input(&pFmtCtx, TCHAR_TO_ANSI(*cameraURL), ifmt, &options);
	FFMPEG_IsSaveToArray = false;
	avformat_close_input(&pFmtCtx);

	log = result == 0 ? "Check Result: OK" : "Check Result: Failed\n\n";
	if (result == 0)return true;
	for (int i = 0; i < FFMPEG_LogArray.Num(); i++)
		log += FFMPEG_LogArray[i];
	FFMPEG_LogArray.Empty();
	return false;
}

bool UFFmpegWebcamManager::CheckValid()
{
	if (!daemonActor)return false;
	if (!daemonActor->IsValidLowLevel()) {
		daemonActor = nullptr;
		return false;
	}
	return true;
}

bool UFFmpegWebcamManager::StartMocap() {
	if (mocapExecutor == nullptr) {
		mocapExecutor = new PsyMocapExecutor(this);
	}
	mocapExecutor->Start();
	return true;
}

bool UFFmpegWebcamManager::PauseMocap()
{
	if (mocapExecutor) {
		mocapExecutor->Pause();
	}
	return true;
}

bool UFFmpegWebcamManager::ResumeMocap()
{
	if (mocapExecutor) {
		mocapExecutor->Resume();
	}
	if (mocapExecutor == nullptr) {
		mocapExecutor = new PsyMocapExecutor(this);
	}
	mocapExecutor->Start();
	return true;
}

bool UFFmpegWebcamManager::StopMocap()
{
	if (mocapExecutor) {
		mocapExecutor->Stop();
		mocapExecutor ->~PsyMocapExecutor();
		delete mocapExecutor;
		mocapExecutor = nullptr;

		PsymocapStop();
		PsymocapRelease();
	}
	// avcodec_close(pCodecContext);
	// avformat_close_input(&pFormatContext);
	return true;
}

// FRunnable interface

void UFFmpegWebcamManager::Start()
{
	ThreadName = "Psy Webcam Reader";
	ThreadName.AppendInt(FAsyncThreadIndex::GetNext());
	Stopping = false;

	Thread = FRunnableThread::Create(this, *ThreadName, 128 * 1024, TPri_AboveNormal, FPlatformAffinity::GetPoolThreadMask());
}

void UFFmpegWebcamManager::Stop()
{
	Stopping = true;
}

uint32 UFFmpegWebcamManager::Run()
{
	bool status = false;
	while (!Stopping)
	{
		ReadFrame(status);
	}
	return 0;
}

//PsyMocapExecutor

PsyMocapExecutor::PsyMocapExecutor(UFFmpegWebcamManager* Manager)
	:Stopping(false)
	,Thread(nullptr)
	, ThreadName("PsyMocap Executor")
{
	this->WebcamManager = Manager;
}

PsyMocapExecutor::~PsyMocapExecutor() {
	Stop();
	if (Thread != nullptr)
	{
		Thread->WaitForCompletion();
		delete Thread;
		Thread = nullptr;
	}
}

bool PsyMocapExecutor::Pause() {
	if (Thread != nullptr)
	{
		Thread->Suspend(true);
		return true;
	}
	else {
		return false;
	}
}

bool PsyMocapExecutor::Resume() {
	if (Thread != nullptr)
	{
		Thread->Suspend(false);
		return true;
	}
	else {
		return false;
	}
}

bool PsyMocapExecutor::Init()
{
	return true;
}

void PsyMocapExecutor::Start()
{
	ThreadName.AppendInt(FAsyncThreadIndex::GetNext());
	Stopping = false;

	Thread = FRunnableThread::Create(this, *ThreadName, 128 * 1024, TPri_AboveNormal, FPlatformAffinity::GetPoolThreadMask());
}

void PsyMocapExecutor::Stop()
{
	Stopping = true;
}

uint32 PsyMocapExecutor::Run()
{
	while (!Stopping)
	{
		if (WebcamManager)
		{
			PsyMocapProcessFrame(WebcamManager->ImageBufferRGB.data(), WebcamManager->videoSize.X, WebcamManager->videoSize.Y);
		}
	}
	return 0;
}

void PsyMocapExecutor::Exit()
{
	
}


UnsyInitMocap::UnsyInitMocap(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}
UnsyInitMocap* UnsyInitMocap::CreateUnsyInitMocap( int _port)
{

	
	UnsyInitMocap* InitTask= NewObject<UnsyInitMocap>();
	InitTask->m_port = _port;
	//std::function<void(int)> f1 = std::bind(&UnsyInitMocap::start, InitTask, std::placeholders::_1);

	//std::thread ExcutAsyTask(f1, _port);
	// ExcutAsyTask.detach();
	

	AsyncTask(ENamedThreads::GameThread, [InitTask]() { InitTask->start(); });
	//ExcutAsyTask.join();
	
	//AnsyInitMocap->Start( _port); 
	return InitTask;
}
void UnsyInitMocap::start(){
#if !UE_SERVER
	

	int ret = -1;
	if (PsyMocapInit) 
	{
		PsyMocapInit(m_port);
		ret = 1;
	}
	else {
		ret = 0;
	}
	//PsymocapRelease();
	//std::this_thread::sleep_for(std::chrono::seconds(5));
	OnInit.Broadcast(ret);
#endif
}