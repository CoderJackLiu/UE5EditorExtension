// Copyright Epic Games, Inc. All Rights Reserved.

#include "FFmpegWebcamUnreal.h"
#include "PsyMocapSDK.h"

#define LOCTEXT_NAMESPACE "FFFmpegWebcamUnrealModule"

void FFFmpegWebcamUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// TCHAR exeFullPath[MAX_PATH];
	// GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	// std::wstring strFullPath = (std::wstring)(exeFullPath);
	// int indx = 4;
	// std::wstring strExeName = strFullPath;
	// while (indx > 0) {
	// 	int nStart = strExeName.find_last_of(TEXT("\\"));
	// 	strExeName = strExeName.substr(0, nStart);
	// 	indx--;
	// };
	// std::function<std::string(std::wstring)> w2s = [](std::wstring wstr) {
	// 	// unsigned len = str.size() * 4;
	//    //  setlocale(LC_CTYPE, "C");
	//    //  char* p = new char[len];
	//    // wcstombs(p, str.c_str(), len);
	//    //  std::string str1(p);
	// 	// delete[] p;
	//   //  return str1;
	//
	// 	std::string result;
	// 	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	// 	char* buffer = new char[len + 1];
	//
	// 	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	// 	buffer[len] = '\0';
	// 	result.append(buffer);
	// 	delete[] buffer;
	// 	return result;
	//
	//
	// };
	// std::string libPath = w2s(strExeName);
	// char* p;
	// p = getenv("Path");
	// std::string env(p);
	// std::string newenv;
	// newenv = "Path=" + env + libPath + "\\lib;";
	// putenv(newenv.c_str());



	av_log_set_callback(&FFMPEG_LogCallback);

	InitPsyMocapAPI();
}

void FFFmpegWebcamUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FFMPEG_LogCallback(void* ptr, int level, const char* fmt, va_list vl)
{
	if (FFMPEG_IsSaveToArray)
	{
		char buffer[1024];
		vsprintf(buffer, fmt, vl);
		FFMPEG_LogArray.Add(buffer);
	}
}

void InitPsyMocapAPI() {
	hPsyMocapModule = (HMODULE)FPlatformProcess::GetDllHandle(TEXT("MocapDll.dll"));
	if (hPsyMocapModule) {
		PsyMocapInit = (PSYMOCAP_API_INIT)FPlatformProcess::GetDllExport(hPsyMocapModule, TEXT("init"));
		PsyMocapProcessFrame = (PSYMOCAP_API_PROCESSFRAME)FPlatformProcess::GetDllExport(hPsyMocapModule, TEXT("processFrame"));
		PsymocapStop = (PSYMOCAP_API_STOP)FPlatformProcess::GetDllExport(hPsyMocapModule, TEXT("stop"));
		PsymocapRelease = (PSYMOCAP_API_RELEASE)FPlatformProcess::GetDllExport(hPsyMocapModule, TEXT("release"));
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFFmpegWebcamUnrealModule, FFmpegWebcamUnreal)