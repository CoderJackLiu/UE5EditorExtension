#include "CustomMeshAssetEditorViewport.h"

#include "CustomMeshEditorViewportClient.h"

void SCustomMeshAssetEditorViewport::Construct(const FArguments& InArgs)
{
	CustomMesh = InArgs._CustomMesh.Pin();

	SEditorViewport::Construct(SEditorViewport::FArguments());

	PreviewScene->SetFloorVisibility(false);
	PreviewScene->SetEnvironmentVisibility(false);
	PreviewScene->SetSkyBrightness(0.0f);
	PreviewScene->SetFloorOffset(-10000.0f);
	PreviewScene->SetLightBrightness(0.0f);
	
}

SCustomMeshAssetEditorViewport::SCustomMeshAssetEditorViewport(): PreviewScene(MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues())))
{
	
}

SCustomMeshAssetEditorViewport::~SCustomMeshAssetEditorViewport()
{
	// CastChecked<UEditorEngine>(GEngine)->OnPreviewFeatureLevelChanged().Remove(PreviewFeatureLevelChangedHandle);

	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
	if (EditorViewportClient.IsValid())
	{
		EditorViewportClient->Viewport = nullptr;
	}
}

void SCustomMeshAssetEditorViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
}

void SCustomMeshAssetEditorViewport::UpdatePreviewSocketMeshes()
{
}

void SCustomMeshAssetEditorViewport::RefreshViewport()
{
	
}

TSharedRef<FEditorViewportClient> SCustomMeshAssetEditorViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable( new FCustomMeshEditorViewportClient(SharedThis(this), PreviewScene.ToSharedRef(), StaticMesh, NULL) );

	EditorViewportClient->bSetListenerPosition = false;

	EditorViewportClient->SetRealtime( true );
	EditorViewportClient->VisibilityDelegate.BindSP( this, &SCustomMeshAssetEditorViewport::IsVisible );

	return EditorViewportClient.ToSharedRef();
}

void SCustomMeshAssetEditorViewport::SetPreviewMesh(UStaticMesh* InStaticMesh)
{
	
}
