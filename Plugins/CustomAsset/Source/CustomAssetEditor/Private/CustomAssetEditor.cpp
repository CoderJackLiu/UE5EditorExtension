#include "CustomAssetEditor.h"

#include "CustomMesh.h"
#include "CustomMeshActionBase.h"
#include "CustomMeshSettings.h"
#include "CustomMeshThumbnail.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"


void FCustomAssetEditorModule::StartupModule()
{
	RegisterCustomMeshActions();
	// Register the thumbnail renderer for our custom asset type
	UThumbnailManager::Get().RegisterCustomRenderer(UCustomMesh::StaticClass(), UCustomMeshThumbnail::StaticClass());

	RegisterCustomMeshSettings();
}


void FCustomAssetEditorModule::ShutdownModule()
{
	UnRegisterCustomMeshActions();
	// Unregister the thumbnail renderer
	if (UObjectInitialized())
	{
		UThumbnailManager::Get().UnregisterCustomRenderer(UCustomMesh::StaticClass());
	}
	UnRegisterCustomMeshSettings();
}

void FCustomAssetEditorModule::RegisterCustomMeshSettings()
{
	// 注册设置
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Project", "CustomMeshSettings",
		                                 NSLOCTEXT("CustomAsset", "CustomSettingsName", "CustomMeshSettings"),
		                                 NSLOCTEXT("CustomAsset", "Custom Mesh Settings", "Configure my custom Mesh Plugin settings"),
		                                 GetMutableDefault<UCustomMeshSettings>()
		);
	}
}

void FCustomAssetEditorModule::RegisterCustomMeshActions()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Category = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("YourCategory")), LOCTEXT("YourCategory", "YourCategory"));
	Action = MakeShareable(new FCustomMeshActionBase());
	AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
}

void FCustomAssetEditorModule::UnRegisterCustomMeshActions()
{
	//log
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
	}
}

void FCustomAssetEditorModule::UnRegisterCustomMeshSettings()
{
	// 注销设置
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "MyCategory", "MySettings");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)
