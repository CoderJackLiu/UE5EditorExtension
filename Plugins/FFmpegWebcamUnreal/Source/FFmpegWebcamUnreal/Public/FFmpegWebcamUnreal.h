// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
};


class FFFmpegWebcamUnrealModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FFMPEG_LogCallback(void* ptr, int level, const char* fmt, va_list vl);
bool FFMPEG_IsSaveToArray;
TArray<FString> FFMPEG_LogArray;

void InitPsyMocapAPI();