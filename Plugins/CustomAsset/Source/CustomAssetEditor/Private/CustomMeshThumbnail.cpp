// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMeshThumbnail.h"

#include "CustomMesh.h"
#include "RenderingThread.h"
#include "ThumbnailHelpers.h"


void UCustomMeshThumbnail::Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily)
{
	const UCustomMesh* CustomMesh = Cast<UCustomMesh>(Object);
	if (CustomMesh && IsValid(CustomMesh->GetStaticMesh()))
	{
		if (ThumbnailScene == nullptr|| ensure(ThumbnailScene->GetWorld() != nullptr) == false)
		{
			if (ThumbnailScene)
			{
				FlushRenderingCommands();
				delete ThumbnailScene;
			}
			ThumbnailScene = new FStaticMeshThumbnailScene();
		}

		ThumbnailScene->SetStaticMesh(CustomMesh->GetStaticMesh());
		ThumbnailScene->GetScene()->UpdateSpeedTreeWind(0.0);

		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(RenderTarget, ThumbnailScene->GetScene(), FEngineShowFlags(ESFIM_Game))
			.SetTime(UThumbnailRenderer::GetTime())
			.SetAdditionalViewFamily(bAdditionalViewFamily));

		ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
		ViewFamily.EngineShowFlags.MotionBlur = 0;
		ViewFamily.EngineShowFlags.LOD = 0;

		RenderViewFamily(Canvas, &ViewFamily, ThumbnailScene->CreateView(&ViewFamily, X, Y, Width, Height));
		ThumbnailScene->SetStaticMesh(nullptr);
	}
}

bool UCustomMeshThumbnail::CanVisualizeAsset(UObject* Object)
{
	const UCustomMesh* CustomMesh = Cast<UCustomMesh>(Object);
	// return CustomMesh && CustomMesh->GetStaticMesh();
	return true;
}

void UCustomMeshThumbnail::BeginDestroy()
{
	if (ThumbnailScene != nullptr)
	{
		delete ThumbnailScene;
		ThumbnailScene = nullptr;
	}

	Super::BeginDestroy();
}
