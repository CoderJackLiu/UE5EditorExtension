// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomMeshSettings.generated.h"

/**
 * 
 */
UCLASS(config=Editor, defaultconfig)
class CUSTOMASSETEDITOR_API UCustomMeshSettings : public UObject
{
	GENERATED_BODY()
	UCustomMeshSettings();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:

	//get static mesh import path
	FString GetStaticMeshImportPath() const { return StaticMeshImportPath.Path; }

	//get save after import success
	bool GetSaveAfterImport() const { return bSaveAfterImport; }


private:
	//Global settings
	//Auto save asset Path for reference staticMesh
	UPROPERTY(EditAnywhere, config, Category="Path Settings", meta = (/*EditCondition="bUseModernXcode",*/ DisplayName = "FBX导入后StaticMesh保存路径",LongPackageName))
	FDirectoryPath StaticMeshImportPath;

	//save after import success
	UPROPERTY(EditAnywhere, config, Category="Path Settings", meta = (/*EditCondition="bUseModernXcode",*/ DisplayName = "FBX导入后保存",LongPackageName,ConfigRestartRequired = true))
	bool bSaveAfterImport;
	
};
