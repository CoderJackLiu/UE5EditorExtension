// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorOperationSubsystem.h"

#include "EditorOperationSetting.h"
#include "Selection.h"

UEditorOperationSubsystem::UEditorOperationSubsystem()
{
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

// void UEditorOperationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
// {
// 	Super::Initialize(Collection);
// 	UEditorOperationSubsystem* EditorConfig = Collection.InitializeDependency<UEditorOperationSubsystem>();
//
//
// 	
// }

int32 UEditorOperationSubsystem::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	return Super::GetFunctionCallspace(Function, Stack);
}

void UEditorOperationSubsystem::OnActorAdded_Implementation(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Added!"));
}

// void UEditorOperationSubsystem::OnActorAdded(AActor* InActor)
// {
// 	// if (InActor&&InActor->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
// 	// {
// 	// 	IEditorOperationInterface* TheInterface = Cast<IEditorOperationInterface>(InActor);
// 	// 	if (TheInterface)
// 	// 	{
// 	// 		// TheInterface->Execute_OnActorAdded(InActor);
// 	// 	}
// 	// }
// 	UE_LOG(LogTemp, Warning, TEXT("Actor Added!"))
//
// }

// void UEditorOperationSubsystem::OnActorMoved(AActor* InActor)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Actor Added!"))
// 	if (GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
// 	{
// 		IEditorOperationInterface::Execute_OnActorMoved(this,InActor);
// 	}
// }

void UEditorOperationSubsystem::OnActorDeleted(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor OnActorDeleted!"))
}

void UEditorOperationSubsystem::OnActorsMoved(TArray<AActor*>& InActors)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor OnActorsMoved!"))
}

void UEditorOperationSubsystem::OnEditorSelectionChanged(UObject* NewSelection)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEditorSelectionChanged!"))
}
