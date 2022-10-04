// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorOperationSubsystem.h"

#include "EditorOperationSetting.h"
#include "Selection.h"

UEditorOperationSubsystem::UEditorOperationSubsystem()
{
}

void UEditorOperationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UEditorOperationSubsystem* EditorConfig = Collection.InitializeDependency<UEditorOperationSubsystem>();


	//Editor world operation
	{
		//编辑器世界：Actor添加到世界绑定；
		GEngine->OnLevelActorAdded().AddUObject(this, &UEditorOperationSubsystem::OnActorAdded);

		//编辑器世界：Actor删除事件绑定；
		GEngine->OnLevelActorDeleted().AddUObject(this, &UEditorOperationSubsystem::OnActorDeleted);

		//编辑器世界：Actor移动事件绑定；
		GEngine->OnActorMoved().AddUObject(this, &UEditorOperationSubsystem::OnActorMoved);

		//编辑器世界：多个Actor被移动事件绑定；
		GEngine->OnActorsMoved().AddUObject(this, &UEditorOperationSubsystem::OnActorsMoved);
	}

	//content Browser Operation & Editor world
	{
		USelection::SelectionChangedEvent.AddUObject(this, &UEditorOperationSubsystem::OnEditorSelectionChanged);
	}
}

int32 UEditorOperationSubsystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}

void UEditorOperationSubsystem::OnActorAdded(AActor* InActor)
{
	// if (InActor&&InActor->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	// {
	// 	IEditorOperationInterface* TheInterface = Cast<IEditorOperationInterface>(InActor);
	// 	if (TheInterface)
	// 	{
	// 		// TheInterface->Execute_OnActorAdded(InActor);
	// 	}
	// }
}

void UEditorOperationSubsystem::OnActorMoved(AActor* InActor)
{
}

void UEditorOperationSubsystem::OnActorDeleted(AActor* InActor)
{
}

void UEditorOperationSubsystem::OnActorsMoved(TArray<AActor*>& InActors)
{
	const FString Path = UEditorOperationSetting::Get()->GetWidgetInstancePath();
	TSubclassOf<UEditorUtilityWidget> ClassInstance = LoadClass<UEditorUtilityWidget>(nullptr, *Path);
	if (ClassInstance && ClassInstance->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	{
		if (auto Interface = Cast<IEditorOperationInterface>(ClassInstance))
		{
			Interface->OnActorsMoved(InActors);
		}
	}
}

void UEditorOperationSubsystem::OnEditorSelectionChanged(UObject* NewSelection)
{
}
