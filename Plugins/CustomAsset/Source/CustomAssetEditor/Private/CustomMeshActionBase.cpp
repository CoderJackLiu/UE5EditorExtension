// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMeshActionBase.h"

#include "CanvasTypes.h"
#include "CustomMesh.h"
#include "CustomMeshEditorToolKit.h"
#include "ThumbnailRendering/SceneThumbnailInfo.h"

TSharedPtr<SWidget> FCustomMeshActionBase::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	// FTextureRenderTargetResource* ThumbnailRTResource=nullptr;
	//
	// FThumbnailRenderingInfo* RenderingInfo = UThumbnailManager::Get().GetRenderingInfo(AssetData.GetAsset());
	// if (RenderingInfo != nullptr)
	// {
	// 	if (RenderingInfo->Renderer)
	// 	{
	// 		// RenderingInfo->Renderer->Draw(AssetData.GetAsset(), 0, 0, 128, 128, nullptr, nullptr, false);
	// 		// Re-render
	// 		FCanvas ThumbnailCanvas(ThumbnailRTResource, nullptr, nullptr, ERHIFeatureLevel::Type::SM5, FCanvas::CDM_DeferDrawing, 1.0f);
	// 		RenderingInfo->Renderer->Draw(AssetData.GetAsset(), 0, 0, 128, 128, ThumbnailRTResource, &ThumbnailCanvas, false);
	// 		
	// 		ENQUEUE_RENDER_COMMAND(TransitionThumbnail_RT)
	// 		(
	// 			[RenderTargetResource=ThumbnailRTResource](FRHICommandListImmediate& RHICmdList)
	// 			{
	// 				RHICmdList.Transition(FRHITransitionInfo(RenderTargetResource->GetRenderTargetTexture(), ERHIAccess::RTV, ERHIAccess::SRVMask));
	// 			}
	// 		);
	// 		return SNew(SImage);//.Image(ThumbnailRTResource);
	//
	// 	}
	// }
	AssetData.GetAsset();
	return SNew(SImage).Image(FAppStyle::GetBrush("NoBrush"));
}

EThumbnailPrimType FCustomMeshActionBase::GetDefaultThumbnailPrimitiveType(UObject* Asset) const
{
	return EThumbnailPrimType::TPT_MAX;
}

TArray<FAssetData> FCustomMeshActionBase::GetValidAssetsForPreviewOrEdit(TArrayView<const FAssetData> InAssetDatas, bool bIsPreview)
{
	return FAssetTypeActions_Base::GetValidAssetsForPreviewOrEdit(InAssetDatas, bIsPreview);
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

UThumbnailInfo* FCustomMeshActionBase::GetThumbnailInfo(UObject* Asset) const
{
	UCustomMesh* Outer = CastChecked<UCustomMesh>(Asset);
	return NewObject<USceneThumbnailInfo>(Outer, NAME_None, RF_Transactional);
}


void FCustomMeshActionBase::OpenAssetEditor(const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto InObj = InObjects.CreateConstIterator(); InObj; ++InObj)
	{
		UCustomMesh* CustomMesh = Cast<UCustomMesh>(*InObj);
		if (CustomMesh != nullptr)
		{
			TSharedRef<FCustomMeshEditorToolKit> CustomMeshEditorToolKit = MakeShareable(new FCustomMeshEditorToolKit());
			CustomMeshEditorToolKit->InitCustomMeshEditor(Mode, EditWithinLevelEditor, CustomMesh);
		}
	}
}
