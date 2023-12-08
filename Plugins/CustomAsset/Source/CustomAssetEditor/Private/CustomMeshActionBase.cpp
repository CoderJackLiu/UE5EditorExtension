// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMeshActionBase.h"

#include "CustomMesh.h"

FText FCustomMeshActionBase::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomMeshAsset", "Custom Mesh Asset");
}

UClass* FCustomMeshActionBase::GetSupportedClass() const
{
	return UCustomMesh::StaticClass();
}

FColor FCustomMeshActionBase::GetTypeColor() const
{
	return FColor::Magenta;
}

uint32 FCustomMeshActionBase::GetCategories()
{
	// log
			
	return EAssetTypeCategories::UI;
}
