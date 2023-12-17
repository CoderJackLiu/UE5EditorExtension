#include "CustomMeshAssetEditorViewport.h"

#include "CustomMesh.h"
#include "CustomMeshEditorViewportClient.h"

void SCustomMeshAssetEditorViewport::Construct(const FArguments& InArgs)
{
	CustomMesh = InArgs._InCustomMesh.Get();

	SEditorViewport::Construct(SEditorViewport::FArguments());

	PreviewScene->SetFloorVisibility(false);
	PreviewScene->SetEnvironmentVisibility(true);
	PreviewScene->SetSkyBrightness(1.0f);
	PreviewScene->SetFloorOffset(-10000.0f);
	PreviewScene->SetLightBrightness(0.6f);
	if (CustomMesh)
	{
		SetPreviewMesh(CustomMesh->GetStaticMesh());
	}
}

SCustomMeshAssetEditorViewport::SCustomMeshAssetEditorViewport(): PreviewScene(MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()))), CurrentViewMode(VMI_Wireframe/*VMI_Lit*/)
{
	//log
	UE_LOG( LogTemp, Warning, TEXT( "SCustomMeshAssetEditorViewport::SCustomMeshAssetEditorViewport()" ) );
	
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
	Collector.AddReferencedObject(StaticMesh);
	Collector.AddReferencedObject(PreviewMeshComponent);
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
	StaticMesh = InStaticMesh;
	if (PreviewMeshComponent)
	{
		PreviewScene->RemoveComponent(PreviewMeshComponent);
		PreviewMeshComponent = NULL;
	}
	PreviewMeshComponent = NewObject<UStaticMeshComponent>();
	const ERHIFeatureLevel::Type FeatureLevel = GEditor->PreviewPlatform.GetEffectivePreviewFeatureLevel();
	if ( FeatureLevel <= ERHIFeatureLevel::ES3_1)
	{
		PreviewMeshComponent->SetMobility(EComponentMobility::Static);
	}
	PreviewMeshComponent->SetStaticMesh(StaticMesh);
	PreviewScene->AddComponent(PreviewMeshComponent,FTransform::Identity);
	PreviewMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);


}
