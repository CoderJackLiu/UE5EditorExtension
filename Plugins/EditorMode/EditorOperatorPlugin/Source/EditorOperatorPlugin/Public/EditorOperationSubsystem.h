// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorOperationInterface.h"
#include "UObject/Object.h"
#include "EditorOperationSubsystem.generated.h"

/**
 * This is an unreal editor operation subsystem plugin with the following Features:
 * ① Interface for editor world operations;
 * ② Interface for editor content browser operations;
 * ③ Project Settings for Plugin Features;
 * ④ 
 * ⑤
 */
UCLASS()
class EDITOROPERATORLISTENER_API UEditorOperationSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UEditorOperationSubsystem();

	virtual ~UEditorOperationSubsystem() override {};


	/** Override to control if the Subsystem should be created at all.
	 * For example you could only have your system created on servers.
	 * It's important to note that if using this is becomes very important to null check whenever getting the Subsystem.
	 *
	 * Note: This function is called on the CDO prior to instances being created!
	 *
	 */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;


	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override{};

	/** Overridden to check global network context */
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;

	//editor world operation functions
	
	//编辑器世界：添加Actor触发
	void OnActorAdded(AActor* InActor);

	//编辑器世界：Actor被移动
	void OnActorMoved(AActor* InActor);

	//编辑器世界：Actor被删除 
	void OnActorDeleted(AActor* InActor);

	//编辑器世界：多个Actor被移动
	void OnActorsMoved(TArray<AActor*>& InActors);	

	
	//编辑器：选中ContentBrowser资源或者编辑器世界Actor发生变化
	void OnEditorSelectionChanged(UObject* NewSelection);
	
	
	
};
