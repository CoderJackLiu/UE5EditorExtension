// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetFactory.h"

#include "CustomMesh.h"

UCustomAssetFactory::UCustomAssetFactory()
{
	bCreateNew =true;
	bEditAfterNew = true;
	SupportedClass = UCustomMesh::StaticClass();
}

UObject* UCustomAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	// Make sure we are trying to factory a skeleton, then create and init one


	return  NewObject<UCustomMesh>(InParent, Class, Name, Flags| RF_Transactional);
}
