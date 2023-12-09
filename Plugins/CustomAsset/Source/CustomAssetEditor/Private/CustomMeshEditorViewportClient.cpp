#include "CustomMeshEditorViewportClient.h"
#include  "CustomMeshAssetEditorViewport.h"

FCustomMeshEditorViewportClient::FCustomMeshEditorViewportClient(const TSharedRef<SCustomMeshAssetEditorViewport>& InStaticMeshEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene,
	UStaticMesh* InPreviewStaticMesh, UStaticMeshComponent* InPreviewStaticMeshComponent): FEditorViewportClient(nullptr, &InPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(InStaticMeshEditorViewport))
{
	
}

FCustomMeshEditorViewportClient::~FCustomMeshEditorViewportClient()
{
	
}
