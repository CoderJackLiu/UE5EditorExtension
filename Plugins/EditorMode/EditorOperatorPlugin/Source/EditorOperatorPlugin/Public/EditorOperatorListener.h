// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "ILevelEditor.h"
#include "Modules/ModuleManager.h"

class FEditorOperatorListenerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void CB_SelectedProps();

	/*绑定编辑器世界内的相关操作*/
	void BindingEditorWorldOperations();

	/*绑定ContentBrowser相关操作*/
	void BindingContentBrowserOperations();

	/*绑定PIE相关操作*/
	void BindingPIROperations();
	
	//编辑器：选中ContentBrowser资源或者编辑器世界Actor发生变化
	void OnEditorSelectionChanged(UObject* NewSelection);

	//编辑器世界：添加Actor触发
	void OnActorAdded(AActor* InActor);

	//编辑器世界：Actor被移动
	void OnActorMoved(AActor* InActor);

	//编辑器世界：Actor被删除 
	void OnActorDeleted(AActor* InActor);

	//编辑器：有Object被选中，EditorUtilityWidget除外(目前只发现这一种不会触发)
	/** Called when element selection changes */
	void OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh = false);

	/** Called when actor selection changes */
	void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);

	///////////////////////////////

	/** Called to set property editors to show the given actors, even if those actors aren't in the current selection set */
	void OnOverridePropertyEditorSelection(const TArray<AActor*>& NewSelection, bool bForceRefresh = false);

	////////////////////////////////////////////////

	/** On level changed */
	void OnMapChanged(UWorld* World, EMapChangeType MapChangeType);

	/** On level Opened */
	void OnMapOpened(const FString& Filename, bool bLoadAsTemplate);

	/*当编辑器创建时*/
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);

	/*编辑器视口刷新时*/
	void OnRedrawLevelEditingViewports(bool bInvalidateHitProxies);

	/** Called when viewport tab content changes. */
	void OnTabContentChanged();

	/*编辑器修改Component触发*/
	void OnComponentsEditedInWorld();
	
	/** Method for taking high res screen shots of viewports */
	void TakeHighResScreenShot();

	///////////////////////////////////////////////
	/*
	 * ContentBrowser 相关事件
	 */
	
	/** Requests a rebuild of the widget list if a widget blueprint was deleted */
	void HandleOnAssetsDeleted(const TArray<UClass*>& DeletedAssetClasses);

	/** Callback for whenever any Filter instance blueprint class gets deleted */
	void OnAssetsPendingDelete(const TArray<UObject*> & ObjectsForDelete);
	
	void OnAssetsBeenDrag(const TArray<FAssetData>& AssetDatas, class UActorFactory* Factory );

	/*Package被删除*/
	void OnPackageDelete(UPackage* PackageForDelete);

	/*新的Asset创建*/
	void HandleOnNewAssetCreate(UFactory* NewAsset);

	/*Asset导入前*/
	void OnAssetPreImport(UFactory* InFactory, UClass* InClass, UObject* InParent, const FName& Name, const TCHAR* Type);

	/*Asset导入后*/
	void OnAssetPostImport(UFactory* InFactory, UObject* InCreatedObject);

	/*Asset 重新导入*/
	void OnAssetReimport(UObject* InObject);

	////////////////////////////////////

	/*PIE相关操作*/

	/*PIE 开始运行*/
	void OnPIEStarted(bool bSimulating);

	/*PIE暂停*/
	void OnPIEPaused(bool bSimulating);

	/*PIE恢复运行*/
	void OnPIEResumed(bool bSimulating);

	/*PIE停止*/
	void OnPIEStopped(bool bSimulating);

	/*PIE单步运行中*/
	void OnPIESingleStepped(bool bSimulating);
	

private:
	static bool bMapHasOpened;
	static UEditorUtilityWidget* WidgetInstance;

	UEditorUtilityWidget* GetWidgetInstance() const;
};
