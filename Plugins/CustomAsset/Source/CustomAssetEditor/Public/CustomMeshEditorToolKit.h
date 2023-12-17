// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FTabManager;

class CUSTOMASSETEDITOR_API FCustomMeshEditorToolKit : public FAssetEditorToolkit
{
public:
	TSharedRef<SDockTab> SpawnTab_CustomMeshEditor(const FSpawnTabArgs& SpawnTabArgs) ;
	
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//initialize
	void InitCustomMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UCustomMesh* InitCustomMesh);

	virtual FName GetToolkitFName() const override ;				
	virtual FText GetBaseToolkitName() const override ;			
	virtual FString GetWorldCentricTabPrefix() const override;


	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	
	
};
