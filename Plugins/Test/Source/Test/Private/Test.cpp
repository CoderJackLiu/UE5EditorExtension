// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test.h"

#define LOCTEXT_NAMESPACE "FTestModule"

void FTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// UObject* bpAsset = LoadObject<UObject>(NULL, TEXT("/EditorOperatorListener/BP_EditorOperationSystem.BP_EditorOperationSystem"));

}

void FTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestModule, Test)