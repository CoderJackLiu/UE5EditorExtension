// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomMesh.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMASSET_API UCustomMesh : public UObject
{
	GENERATED_BODY()

public:



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="CustomMesh")
	TObjectPtr<class UStaticMesh> StaticMesh;
	
};
