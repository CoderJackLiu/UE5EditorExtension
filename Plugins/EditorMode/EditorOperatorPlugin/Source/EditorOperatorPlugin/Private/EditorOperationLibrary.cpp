// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorOperationLibrary.h"

#include "Selection.h"

void UEditorOperationLibrary::GetSelectedObjects(TArray<UObject*>& SelectedObjects)
{
	GEditor->GetSelectedActors()->GetSelectedObjects(AActor::StaticClass(), /*out*/ SelectedObjects);
}

void UEditorOperationLibrary::GetSelectedActors(TArray<AActor*>& SelectedObjects)
{
	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedObjects);
}
