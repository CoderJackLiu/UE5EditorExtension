#include "EditorTest.h"

#define LOCTEXT_NAMESPACE "FEditorTestModule"

void FEditorTestModule::StartupModule()
{
}

void FEditorTestModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FEditorTestModule, EditorTest)