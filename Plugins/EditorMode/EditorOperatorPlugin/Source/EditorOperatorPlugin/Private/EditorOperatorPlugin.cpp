// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorOperatorPlugin.h"

#include "Selection.h"
#include "Editor.h"
#include "LevelEditor.h"
#define LOCTEXT_NAMESPACE "FEditorOperatorPluginModule"

void FEditorOperatorPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FEditorDelegates::SelectedProps.AddRaw(this, &FEditorOperatorPluginModule::CB_SelectedProps);
	//USelection::SelectionChangedEvent.AddUObject(this, &FEditorOperatorPluginModule::OnEditorSelectionChanged);
	// TArray<UObject*> SelectedActors;
	// GEditor->GetSelectedActors()->GetSelectedObjects(AActor::StaticClass(), /*out*/ SelectedActors);


	GEngine->OnLevelActorAdded().AddRaw(this, &FEditorOperatorPluginModule::OnActorChangedSomehow);
	GEngine->OnLevelActorDeleted().AddRaw(this, &FEditorOperatorPluginModule::OnActorChangedSomehow);
	GEngine->OnActorMoved().AddRaw(this, &FEditorOperatorPluginModule::OnActorChangedSomehow);
	GEngine->OnActorsMoved().AddRaw(this, &FEditorOperatorPluginModule::OnActorsChangedSomehow);
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorModule.OnElementSelectionChanged().AddRaw(this, &FEditorOperatorPluginModule::OnElementSelectionChanged);
	LevelEditorModule.OnActorSelectionChanged().AddRaw(this, &FEditorOperatorPluginModule::OnActorSelectionChanged);
}

void FEditorOperatorPluginModule::ShutdownModule()
{
}

void FEditorOperatorPluginModule::CB_SelectedProps()
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed?"))
}

void FEditorOperatorPluginModule::OnEditorSelectionChanged(UObject* NewSelection)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed 2222?"))
}

void FEditorOperatorPluginModule::OnActorChangedSomehow(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed 2222?"))
}

void FEditorOperatorPluginModule::OnActorsChangedSomehow(TArray<AActor*>& InActors)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed 2222?"))
}

void FEditorOperatorPluginModule::OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed 2222?"))
	//const AActor* Actor = Cast<AActor>(SelectionSet);
	
	TArray<AActor*> SelectedActorsdd;
	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActorsdd);
	
	if ( USelection* SelectedActors = GEditor->GetSelectedActors() )
	{
		for ( AActor* Actor : SelectedActorsdd )
		{
			if ( SelectedActors->IsSelected( Actor ) )
			{
				SelectedActors->Deselect( Actor );
			}
		}
	}

}

void FEditorOperatorPluginModule::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed 2222?"))
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorOperatorPluginModule, EditorOperatorPlugin)
