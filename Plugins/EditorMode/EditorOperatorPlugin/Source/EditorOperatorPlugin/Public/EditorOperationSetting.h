// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blutility/Classes/EditorUtilityWidget.h"
#include "UObject/Object.h"
#include "EditorOperationSetting.generated.h"

/**
 * define a config file which has it`s own config file loading and saving func;
 */
UCLASS(config=Project, defaultconfig)
class EDITOROPERATORLISTENER_API UEditorOperationSetting : public UObject
{
	GENERATED_BODY()

public:
	static UEditorOperationSetting* Get() { return GetMutableDefault<UEditorOperationSetting>(); }

	FString GetWidgetInstancePath() const { return InstanceWidget.ToString(); };


	//properties
private:
	UPROPERTY(EditAnywhere, config, Category = Interaction)
	bool Test;

	//
	UPROPERTY(EditAnywhere, config, Category = Instance, meta = (MetaClass = "WidgetBlueprint", AllowPrivateAccess = "true"))
	FSoftObjectPath InstanceWidget;
	
	UPROPERTY(EditAnywhere, config, Category = Instance, meta = (DisplayName="复写实体",MetaClass = "LevelScriptActor", AllowPrivateAccess = "true"))
	FSoftObjectPath LevelScriptInstance;


	
	UPROPERTY(EditAnywhere, config, Category = Rendering)
	TSoftObjectPtr<UMaterialParameterCollection> MaterialParameterCollection;

private:
	// #if WITH_EDITOR
	// 	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// 	virtual bool CanEditChange(const FProperty* InProperty) const override { return true; };
	// #endif
};
