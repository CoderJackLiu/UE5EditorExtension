#pragma once
#include "SAssetEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class FAdvancedPreviewScene;
class UCustomMesh;

class SCustomMeshAssetEditorViewport:public SAssetEditorViewport, public FGCObject//, public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(SCustomMeshAssetEditorViewport)
	{}
	SLATE_ARGUMENT(TWeakPtr<UCustomMesh>, CustomMesh)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	SCustomMeshAssetEditorViewport();
	virtual ~SCustomMeshAssetEditorViewport() override;

	// FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("CustomMeshAssetEditorViewport");
	}
	// End of FGCObject interface

	/** Constructs, destroys, and updates preview mesh components based on the preview static mesh's sockets. */
	void UpdatePreviewSocketMeshes();

	void RefreshViewport();

	/** Component for the preview static mesh. */
	TObjectPtr<UStaticMeshComponent> PreviewMeshComponent;

	/** Component for the preview static mesh. */
	TArray<TObjectPtr<UStaticMeshComponent>> SocketPreviewMeshComponents;

	// UPROPERTY(Transient)
	TSharedPtr<UCustomMesh> CustomMesh;
	
	TSharedPtr<UCustomMesh> GetCustomMesh() const
	{
		return CustomMesh;
	}


	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	// virtual EVisibility OnGetViewportContentVisibility() const override;
	// virtual void BindCommands() override;
	// virtual void OnFocusViewportToSelection() override;
	// virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	// virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;

	//todo  ICommonEditorViewportToolbarInfoProvider interface
	
	// // Get the viewport widget
	// virtual TSharedRef<class SEditorViewport> GetViewportWidget() = 0;
	//
	// // 	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	// // 	TSharedPtr<FExtender> LevelEditorExtenders = LevelEditorModule.GetMenuExtensibilityManager()->GetAllExtenders();
	// virtual TSharedPtr<FExtender> GetExtenders() const = 0;
	//
	// // Called to inform the host that a button was clicked (typically used to focus on a particular viewport in a multi-viewport setup)
	// virtual void OnFloatingButtonClicked() = 0;
	
private:
	/**
 *	Sets up the static mesh that the Static Mesh editor is viewing.
 *
 *	@param	InStaticMesh		The static mesh being viewed in the editor.
 */
	void SetPreviewMesh(UStaticMesh* InStaticMesh);



	
private:

	/** The parent tab where this viewport resides */
	TWeakPtr<SDockTab> ParentTab;

	/** The scene for this viewport. */
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;

	/** Editor viewport client */
	TSharedPtr<class FCustomMeshEditorViewportClient> EditorViewportClient;

	/** Static mesh being edited */
	TObjectPtr<UStaticMesh> StaticMesh;

	/** The currently selected view mode. */
	EViewModeIndex CurrentViewMode;
	
	// /** Handle to the registered OnPreviewFeatureLevelChanged delegate. */
	// FDelegateHandle PreviewFeatureLevelChangedHandle;
};
