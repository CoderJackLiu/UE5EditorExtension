#pragma once
#include "AdvancedPreviewScene.h"


class SCustomMeshAssetEditorViewport;

class FCustomMeshEditorViewportClient:public FEditorViewportClient, public TSharedFromThis<FCustomMeshEditorViewportClient>
{
public:
	FCustomMeshEditorViewportClient(/*TWeakPtr<IStaticMeshEditor> InStaticMeshEditor,*/ const TSharedRef<SCustomMeshAssetEditorViewport>& InStaticMeshEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene, UStaticMesh* InPreviewStaticMesh, UStaticMeshComponent* InPreviewStaticMeshComponent);
	virtual ~FCustomMeshEditorViewportClient() override;

	// FEditorViewportClient interface
	// virtual void MouseMove(FViewport* Viewport,int32 x, int32 y) override;
	// virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	// virtual bool InputAxis(FViewport* Viewport, FInputDeviceId DeviceId, FKey Key, float Delta, float DeltaTime, int32 NumSamples=1, bool bGamepad=false) override;
	// virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;
	// virtual void Tick(float DeltaSeconds) override;
	// virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;
	// virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;
	// virtual bool InputWidgetDelta( FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale ) override;
	// virtual void TrackingStarted( const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge ) override;
	// virtual void TrackingStopped() override;
	// virtual UE::Widget::EWidgetMode GetWidgetMode() const override;
	// virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override;
	// virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;
	// virtual bool CanCycleWidgetMode() const override;
	// virtual FVector GetWidgetLocation() const override;
	// virtual FMatrix GetWidgetCoordSystem() const override;
	// virtual ECoordSystem GetWidgetCoordSystemSpace() const override;
	// virtual bool ShouldOrbitCamera() const override;

};
