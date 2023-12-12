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
	//getters
	class UStaticMesh* GetStaticMesh() const { return StaticMesh.Get(); }
	//setters
	void SetStaticMesh(class UStaticMesh* InStaticMesh) { StaticMesh = InStaticMesh; }

private:
	UPROPERTY(VisibleAnywhere, Category="CustomMesh", meta=(AllowedClasses="StaticMesh"))
	TObjectPtr<class UStaticMesh> StaticMesh;
};
