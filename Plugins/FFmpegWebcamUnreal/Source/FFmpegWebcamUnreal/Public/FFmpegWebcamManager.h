// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
};

#include "Kismet/BlueprintAsyncActionBase.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
//#include "Interfaces/IHttpRequest.h"
#include "FFmpegWebcamManager.generated.h"

UENUM()
enum EFFMPEG_Platform
{
	FFMPEG_WINDOWS     UMETA(DisplayName = "Windows"),
	FFMPEG_MAC   UMETA(DisplayName = "Mac"),
};

UCLASS()
class FFMPEGWEBCAMUNREAL_API AFFmpegWebcamManagerDaemon : public AActor
{
	GENERATED_BODY()
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	AVFormatContext* pFormatContext;
	AVCodecContext* pCodecContext;
};

class FFMPEGWEBCAMUNREAL_API PsyMocapExecutor;
/**
 * 
 */
UCLASS(Blueprintable)
class FFMPEGWEBCAMUNREAL_API UFFmpegWebcamManager : public UDataAsset, public FRunnable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "FFmpeg Webcam")
	void SetCamera(FString name);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam", meta=(ExpandBoolAsExecs = status))
	void OpenCamera(bool &status);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	void CloseCamera();

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam", meta=(ExpandBoolAsExecs = status))
	void ReadFrame(bool &status);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	void DrawToCanvas(UCanvas* canvas);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	void DrawToRT(UTextureRenderTarget2D* TargetRT);
	
	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	static void GetCameraList(TArray<FString> &list);

	UFUNCTION(BlueprintCallable, Category="FFmpeg Webcam")
	bool CheckCameraAvailable(FString &log);

	UFUNCTION(BlueprintCallable, Category = "FFmpeg Webcam")
	bool StartMocap();

	UFUNCTION(BlueprintCallable, Category = "FFmpeg Webcam")
	bool PauseMocap();

	UFUNCTION(BlueprintCallable, Category = "FFmpeg Webcam")
	bool ResumeMocap();

	UFUNCTION(BlueprintCallable, Category = "FFmpeg Webcam")
	bool StopMocap();
	
	UPROPERTY(EditDefaultsOnly, Category="Webcam Info")
	bool updateCamera;
	
	UPROPERTY(VisibleAnywhere, Category="Webcam Info",Meta=(ShowOnlyInnerProperties)) 
	TArray<FString> cameraList;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config", meta=(ArrayClamp=cameraList))
	int32 cameraIndex = -1;
	
	UPROPERTY(VisibleAnywhere, Category="Webcam Config")
	FString cameraName = "--No Webcam--";

	UPROPERTY(EditAnywhere, Category="Webcam Config", BlueprintReadOnly)
	FIntPoint videoSize;
	
	UPROPERTY(EditAnywhere, Category="Webcam Config")
	float frameRate;

	UPROPERTY(EditDefaultsOnly, Category="Validation")
	bool checkCamera;

	UPROPERTY(VisibleAnywhere, Category="Validation")
	FString checkCameraLog;

	UPROPERTY()
	TArray<int32> imageBufferBRGA;

	UPROPERTY(BlueprintReadWrite, Category="Image Buffer")
	UMaterialInterface* P_Mat;

	UPROPERTY(BlueprintReadWrite,Category="Image Buffer")
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(BlueprintReadWrite,Category="Image Buffer")
	UTexture2D* TextureBuffer;
	
	std::vector<uint8_t> ImageBufferRGB;

	int LiveLinkPort;

	// Begin FRunnable Interface

	virtual bool Init() override { return true; }
	virtual uint32 Run() override;
	void Start();
	virtual void Stop() override;
	virtual void Exit() override
	{
		Stopping = true;
		avcodec_free_context(&pCodecContext);
		avcodec_close(pCodecContext);
		avformat_close_input(&pFormatContext);
		
		pFormatContext=nullptr;
	    videoStream = nullptr;
	    pCodec = nullptr;
	    pCodecContext = nullptr;
	    packet = nullptr;
	    frame = nullptr;
	    Region = nullptr;
	    frame_bgra = nullptr;
	    swsContext_bgra = nullptr;
	    frame_rgb = nullptr;
	    swsContext_rgb = nullptr;
	    daemonActor = nullptr;
		mocapExecutor = nullptr;
		Thread=nullptr;
	}

	// End FRunnable Interface

private:
	AVFormatContext* pFormatContext;
	AVStream* videoStream;
	const AVCodec* pCodec;
	AVCodecContext* pCodecContext;
	AVPacket* packet;
	AVFrame* frame;

	FUpdateTextureRegion2D* Region;
	AVFrame* frame_bgra;
	SwsContext* swsContext_bgra;

	AVFrame* frame_rgb;
	SwsContext* swsContext_rgb;

	AFFmpegWebcamManagerDaemon* daemonActor;

	PsyMocapExecutor* mocapExecutor;

	bool CheckValid();

	// Threadsafe Bool for terminating the main thread loop
	FThreadSafeBool Stopping;

	// Thread to run socket operations on
	FRunnableThread* Thread;

	// Name of the sockets thread
	FString ThreadName;

	// Time to wait between attempted receives
	FTimespan WaitTime;
	UPROPERTY(Transient)
	UTexture2D* Pointer;

};

class FFMPEGWEBCAMUNREAL_API PsyMocapExecutor : public FRunnable
{
public:

    PsyMocapExecutor(UFFmpegWebcamManager* manager);

	virtual ~PsyMocapExecutor();

	bool Pause();
	bool Resume();

	// Begin FRunnable Interface
	virtual bool Init() override;
	virtual uint32 Run() override;
	void Start();
	virtual void Stop() override;
	virtual void Exit() override;
	// End FRunnable Interface
private:

	UFFmpegWebcamManager* WebcamManager;

	// Threadsafe Bool for terminating the main thread loop
	FThreadSafeBool Stopping;

	// Thread to run socket operations on
	FRunnableThread* Thread;

	// Name of the sockets thread
	FString ThreadName;
};

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitMocapDelegate,int32,InitRet);
//DECLARE_DELEGATE_RetVal_OneParam(int,InitMocapDelegate,int);
UCLASS()
class FFMPEGWEBCAMUNREAL_API UnsyInitMocap: public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ))
	static UnsyInitMocap* CreateUnsyInitMocap(int _port);

public:
	UPROPERTY(BlueprintAssignable, Category = "AsyncTaskInitMocap", meta = (DisplayName = "OnPsyInit"))
		FInitMocapDelegate OnInit;
	// UPROPERTY(BlueprintAssignable, Category = "AsyncTaskDownloadFile", meta = (DisplayName = "On Fail"))
	// 	FDownloadFileUnsuccssfullyDelegate OnFail;
public:
	int m_port;
	void start();
};