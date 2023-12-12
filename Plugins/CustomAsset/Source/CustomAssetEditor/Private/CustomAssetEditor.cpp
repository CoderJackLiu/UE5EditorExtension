#include "CustomAssetEditor.h"

#include "CustomMesh.h"
#include "CustomMeshActionBase.h"
#include "CustomMeshThumbnail.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

void FCustomAssetEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Category = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("YourCategory")), LOCTEXT("YourCategory", "YourCategory"));
	Action = MakeShareable(new FCustomMeshActionBase());
	AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());


	UThumbnailManager::Get().RegisterCustomRenderer(UCustomMesh::StaticClass(), UCustomMeshThumbnail::StaticClass());

}

void FCustomAssetEditorModule::ShutdownModule()
{
	//log
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
	}
	if (UObjectInitialized())
	{
		UThumbnailManager::Get().UnregisterCustomRenderer(UCustomMesh::StaticClass());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)
