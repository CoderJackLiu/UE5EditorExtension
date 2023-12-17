// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMeshSettings.h"

UCustomMeshSettings::UCustomMeshSettings()
{
	LoadConfig();
	if (StaticMeshImportPath.Path.IsEmpty())
	{
		StaticMeshImportPath.Path = TEXT("/Game/CustomAsset/StaticMesh");
		SaveConfig();
	}
}

void UCustomMeshSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);

	SaveConfig();
}
