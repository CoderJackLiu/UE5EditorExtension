// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EditorOperationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEditorOperationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EDITOROPERATORLISTENER_API IEditorOperationInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*触发条件：编辑器：ContentBrowser资源或者世界大纲选中Actor变化*/
	/** Called when actor In EditorWorld Or Assets In ContentBrowser selection changes */
	UFUNCTION(BlueprintNativeEvent, Category="EditorOperation|EditorWorld")
	void OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh = false);

	//触发条件：编辑器世界：添加Actor
	//called when Actor been added into editor world
	UFUNCTION(BlueprintNativeEvent, Category="EditorOperation|EditorWorld")
	void OnActorAdded(AActor* InActor);

	//触发条件：编辑器世界：Actor被移动
	//called when Actor been moved in Editor world
	UFUNCTION(BlueprintNativeEvent, Category="EditorOperation|EditorWorld")
	void OnActorMoved(AActor* InActor);

	//触发条件：编辑器世界：Actor被删除
	//Called when Actor been deleted in editor world
	UFUNCTION(BlueprintNativeEvent, Category="EditorOperation|EditorWorld")
	void OnActorDeleted(AActor* InActor);

	/* 触发条件：编辑器世界选中Actor变化 */
	/** Called when actor selection changes */
	UFUNCTION(BlueprintNativeEvent, Category="EditorOperation|EditorWorld&ContentBrowser")
	void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);
};
