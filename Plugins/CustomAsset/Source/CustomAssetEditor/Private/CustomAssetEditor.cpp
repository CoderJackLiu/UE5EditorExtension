#include "CustomAssetEditor.h"

#include "CustomMeshActionBase.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

void FCustomAssetEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Category = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("YourCategory")), LOCTEXT("YourCategory", "YourCategory"));
	const TSharedRef<IAssetTypeActions> Action = MakeShareable(new FCustomMeshActionBase());
	AssetTools.RegisterAssetTypeActions(Action);    
}

void FCustomAssetEditorModule::ShutdownModule()
{
    //log
			
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)