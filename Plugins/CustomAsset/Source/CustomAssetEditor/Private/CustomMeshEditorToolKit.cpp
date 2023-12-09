// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMeshEditorToolKit.h"
#include "Widgets/Images/SImage.h"
#include "Framework/Docking/TabManager.h"
#include "CustomMesh.h"
#include "CustomMeshAssetEditorViewport.h"
#include "CustomMeshEditorViewportClient.h"
#include "EditorStyleSet.h"

const FName CustomMeshEditorID(TEXT("CustomMeshEditor"));
#define LOCTEXT_NAMESPACE "CustomMeshEditorToolKit"

TSharedRef<SDockTab> FCustomMeshEditorToolKit::SpawnTab_CustomMeshEditor(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
	[
		SNew(SCustomMeshAssetEditorViewport)
	];
}

void FCustomMeshEditorToolKit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(CustomMeshEditorID, FOnSpawnTab::CreateRaw(this, &FCustomMeshEditorToolKit::SpawnTab_CustomMeshEditor));
}

void FCustomMeshEditorToolKit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(CustomMeshEditorID);
}

void FCustomMeshEditorToolKit::InitCustomMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UCustomMesh* InitCustomMesh)
{
	const TSharedRef <FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_CustomMeshEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(CustomMeshEditorID, ETabState::OpenedTab)
			)
		);

	InitAssetEditor(Mode, InitToolkitHost, CustomMeshEditorID, StandaloneDefaultLayout, true, true, InitCustomMesh);

	RegenerateMenusAndToolbars();
}

FName FCustomMeshEditorToolKit::GetToolkitFName() const
{
	return FName("SoundEffectPresetEditor");

}

FText FCustomMeshEditorToolKit::GetBaseToolkitName() const
{
	return LOCTEXT("SpriteEditorAppLabel", "Sprite Editor");
}

FString FCustomMeshEditorToolKit::GetWorldCentricTabPrefix() const
{
	return TEXT("SpriteEditor");
}

FLinearColor FCustomMeshEditorToolKit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
#undef LOCTEXT_NAMESPACE
