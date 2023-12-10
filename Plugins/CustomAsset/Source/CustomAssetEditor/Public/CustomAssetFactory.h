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
	GENERATED_UCLASS_BODY()
public:

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled) override;

	/**
	 * Whether the specified file can be imported by this factory.
	 *
	 * @return true if the file is supported, false otherwise.
	 */
	virtual bool FactoryCanImport(const FString& Filename) override;

	/**
	 * Whether the factory is checking for SlowTask::ShouldCancel()
	 * while importing and aborting the import when appropriate.
	 *
	 * @return true if factory import can be canceled.
	 */
	virtual bool CanImportBeCanceled() const override
	{
		return false;
	}

	//get the formats this factory can import
	virtual TArray<FString> GetFormats() const override
	{
		return Formats;
	}
	
	FString AAA;
};


