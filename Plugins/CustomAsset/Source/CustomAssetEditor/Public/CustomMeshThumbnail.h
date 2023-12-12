// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "UObject/Object.h"
#include "CustomMeshThumbnail.generated.h"

/**
 * 
 */
UCLASS(CustomConstructor, Config=Editor)
class CUSTOMASSETEDITOR_API UCustomMeshThumbnail : public UDefaultSizedThumbnailRenderer
{
	GENERATED_UCLASS_BODY()
	
	UCustomMeshThumbnail(const FObjectInitializer& ObjectInitializer)
	:	Super(ObjectInitializer)
	,	ThumbnailScene(nullptr)
	{}

	// UThumbnailRenderer implementation
	virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;
	virtual bool CanVisualizeAsset(UObject* Object) override;
	// UObject implementation
	virtual void BeginDestroy() override;
	virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override { return EThumbnailRenderFrequency::Realtime; }

private:
	class FStaticMeshThumbnailScene* ThumbnailScene;
};
