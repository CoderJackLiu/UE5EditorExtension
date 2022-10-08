// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EditorOperationLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EDITOROPERATORLISTENER_API UEditorOperationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	//获取世界大纲中选中的物体；
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="EditorOperationLibrary")
	static void GetSelectedObjects(TArray<UObject*>& SelectedObjects);

	//获取世界大纲中选中的Actor；
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="EditorOperationLibrary")
	static void GetSelectedActors(TArray<AActor*>& SelectedObjects);

	
	
	
};
