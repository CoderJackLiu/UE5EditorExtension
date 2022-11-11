/*
 * @Author: LIU KANG
 * @Date: 2022-05-11 19:48:11
 * @LastEditors: LIU KANG
 * @LastEditTime: 2022-05-12 16:35:23
 * @FilePath: \psymocapsdk\TestMocapDll\MocapDll.h
 * @Description:
 *
 * Copyright (c) 2022 by 用户/公司名，All Rights Reserved.
 */
#pragma once
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"

#include <windows.h>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#ifndef _PSYMOCAPSDK_H
#define _PSYMOCAPSDK_H

using PSYMOCAP_API_INIT = int(*)(int flag);
using PSYMOCAP_API_PROCESSFRAME = int(*)(void* data, int width, int height);
using PSYMOCAP_API_STOP = int(*)();
using PSYMOCAP_API_RELEASE = int(*)();

PSYMOCAP_API_INIT PsyMocapInit = NULL;
PSYMOCAP_API_PROCESSFRAME PsyMocapProcessFrame = NULL;
PSYMOCAP_API_STOP PsymocapStop = NULL;
PSYMOCAP_API_RELEASE PsymocapRelease = NULL;

HMODULE hPsyMocapModule;

#endif