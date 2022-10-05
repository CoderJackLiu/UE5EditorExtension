// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Modules/ModuleManager.h"

class FEditorOperatorListenerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void CB_SelectedProps();

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

	void OnMapOpened(const FString& Filename, bool bLoadAsTemplate);


private:
	static bool bMapHasOpened;
	static UEditorUtilityWidget* WidgetInstance;

	UEditorUtilityWidget* GetWidgetInstance() const;
};
