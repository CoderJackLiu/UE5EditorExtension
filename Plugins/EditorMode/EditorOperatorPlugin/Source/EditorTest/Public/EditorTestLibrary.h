// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EditorTestLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EDITORTEST_API UEditorTestLibrary : public UObject
{
	GENERATED_BODY()

public:


	//创建Folder
	UFUNCTION(BlueprintCallable,  Category="EditorOperationLibrary")
	static void CreateFolder(const FString& FolderPath);

	//Test
	UFUNCTION(BlueprintCallable,  Category="EditorOperationLibrary")
	static void TestFunc();

	
};
