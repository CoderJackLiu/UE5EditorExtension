// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMASSETEDITOR_API UCustomAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UCustomAssetFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};
