#include "CustomAssetEditor.h"

#include "CustomMeshActionBase.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

void FCustomAssetEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Category = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("YourCategory")), LOCTEXT("YourCategory", "YourCategory"));
	Action = MakeShareable(new FCustomMeshActionBase());
	AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
}

void FCustomAssetEditorModule::ShutdownModule()
{
	//log
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)
