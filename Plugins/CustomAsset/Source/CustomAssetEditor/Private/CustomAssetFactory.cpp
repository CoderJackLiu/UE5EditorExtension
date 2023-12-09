// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetFactory.h"

#include "CustomMesh.h"

UCustomAssetFactory::UCustomAssetFactory()
{
	ImportPriority = 200;
	bCreateNew =true;
	bEditAfterNew = true;
	SupportedClass = UCustomMesh::StaticClass();
	Formats.Empty();
	Formats.Add(TEXT("fbx;FBX meshes and animations"));
	Formats.Add(TEXT("obj;OBJ Static meshes"));
	
}

UObject* UCustomAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	// Make sure we are trying to factory a skeleton, then create and init one


	return  NewObject<UCustomMesh>(InParent, Class, Name, Flags| RF_Transactional);
}

UObject* UCustomAssetFactory::ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled)
{
	
	return Super::ImportObject(InClass, InOuter, InName, Flags, Filename, Parms, OutCanceled);
}

bool UCustomAssetFactory::FactoryCanImport(const FString& Filename)
{
	return Super::FactoryCanImport(Filename);
}
