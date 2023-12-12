// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetFactory.h"

#include "CustomMesh.h"
#include "Factories/SceneImportFactory.h"

UCustomAssetFactory::UCustomAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ImportPriority = 101;
	bCreateNew =true;
	bEditAfterNew = true;
	bEditorImport = true;
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
	if (UFactory* Factory=GetFBXFactory())
	{
		StaticMesh= Factory->ImportObject(InClass, InOuter, InName, Flags, Filename, Parms, OutCanceled);
	}
	//log
	UE_LOG(LogTemp, Warning, TEXT("ImportObject : %s"), StaticMesh? TEXT("true"): TEXT("false"));
	return Super::ImportObject(InClass, InOuter, InName, Flags, Filename, Parms, OutCanceled);
}

bool UCustomAssetFactory::FactoryCanImport(const FString& Filename)
{
	const bool bCanImport = Filename.Contains(".fbx") || Filename.Contains(".obj");
	//log
	UE_LOG(LogTemp, Warning, TEXT("FactoryCanImport : %s"), bCanImport? TEXT("true"): TEXT("false"));
	return bCanImport;
}

UFactory* UCustomAssetFactory::GetFBXFactory()
{
	return GetFactoryInstanceByName(TEXT("FbxFactory"));
}

UFactory* UCustomAssetFactory::GetFactoryInstanceByName(const FString& ClassName)
{
	// 查找类
	UClass* FactoryClass=nullptr;
	for(TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		if(!(*ClassIt)->IsChildOf(UFactory::StaticClass()) || ((*ClassIt)->HasAnyClassFlags(CLASS_Abstract)) || (*ClassIt)->IsChildOf(USceneImportFactory::StaticClass()))
		{
			continue;
		}
		FString SourceClassName=*ClassIt->GetName();
		//log
		UE_LOG(LogTemp, Warning, TEXT("GetFactoryInstanceByName : %s"), *SourceClassName);
		//const UObject* Factory = Cast<UObject>((*ClassIt)->GetDefaultObject());
	
		if (SourceClassName.Equals(ClassName))
		{
			UClass* Class = *ClassIt;
			FactoryClass = Class;
		}
	}
	if (FactoryClass)
	{
		// 创建类的实例
		UFactory* FactoryInstance = NewObject<UFactory>(GetTransientPackage(), FactoryClass);
		return Cast<UFactory>(FactoryInstance);
	}
	return nullptr;
}