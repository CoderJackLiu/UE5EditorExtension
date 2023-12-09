// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMeshActionBase.h"

#include "CustomMesh.h"
#include "CustomMeshEditorToolKit.h"

TSharedPtr<SWidget> FCustomMeshActionBase::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	return SNew(SImage);
}

FText FCustomMeshActionBase::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomMeshAsset", "Custom Mesh Asset");
}

UClass* FCustomMeshActionBase::GetSupportedClass() const
{
	return UCustomMesh::StaticClass();
}

FColor FCustomMeshActionBase::GetTypeColor() const
{
	return FColor::Orange;
}

uint32 FCustomMeshActionBase::GetCategories()
{
	// log
			
	return EAssetTypeCategories::UI;
}

void FCustomMeshActionBase::OpenAssetEditor(const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for(auto InObj=InObjects.CreateConstIterator(); InObj; ++InObj)
	{
		UCustomMesh* CustomMesh = Cast<UCustomMesh>(*InObj);
		if(CustomMesh != nullptr)
		{
			TSharedRef<FCustomMeshEditorToolKit> CustomMeshEditorToolKit = MakeShareable(new FCustomMeshEditorToolKit());
			CustomMeshEditorToolKit->InitCustomMeshEditor(Mode, EditWithinLevelEditor, CustomMesh);
		}
	}
	
}
