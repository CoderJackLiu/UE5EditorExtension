#include "CustomMeshEditorViewportClient.h"
#include  "CustomMeshAssetEditorViewport.h"

FCustomMeshEditorViewportClient::FCustomMeshEditorViewportClient(const TSharedRef<SCustomMeshAssetEditorViewport>& InStaticMeshEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene,
	UStaticMesh* InPreviewStaticMesh, UStaticMeshComponent* InPreviewStaticMeshComponent): FEditorViewportClient(nullptr, &InPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(InStaticMeshEditorViewport))
{
	if (InPreviewStaticMesh&&InPreviewStaticMesh->EditorCameraPosition.bIsSet)
	{
		// The static mesh editor saves the camera position in terms of an orbit camera, so ensure 
		// that orbit mode is enabled before we set the new transform information
		const bool bWasOrbit = bUsingOrbitCamera;
		ToggleOrbitCamera(true);

		SetViewRotation(InPreviewStaticMesh->EditorCameraPosition.CamOrbitRotation);
		SetViewLocation(InPreviewStaticMesh->EditorCameraPosition.CamOrbitPoint + InPreviewStaticMesh->EditorCameraPosition.CamOrbitZoom);
		SetLookAtLocation(InPreviewStaticMesh->EditorCameraPosition.CamOrbitPoint);

		ToggleOrbitCamera(bWasOrbit);
	}
	else
	{
		SetViewLocation( EditorViewportDefs::DefaultPerspectiveViewLocation );
		SetViewRotation( EditorViewportDefs::DefaultPerspectiveViewRotation );	
	}

}

FCustomMeshEditorViewportClient::~FCustomMeshEditorViewportClient()
{
	
}
