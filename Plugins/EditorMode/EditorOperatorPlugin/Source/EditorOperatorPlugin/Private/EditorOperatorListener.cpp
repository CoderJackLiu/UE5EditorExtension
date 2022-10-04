// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorOperatorListener.h"

#include "Selection.h"
#include "Editor.h"
#include "EditorOperationInterface.h"
#include "EditorOperationSetting.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "WidgetBlueprint.h"
#include "UObject/ConstructorHelpers.h"
#define LOCTEXT_NAMESPACE "FEditorOperatorPluginModule"

void RegisterProjectSettings( ISettingsModule& SettingsModule )
{
	// general project settings
	SettingsModule.RegisterSettings("Project", "Project", "General",
		LOCTEXT("EditorOperationSettingsName", "EditorOperationSettings"),
		LOCTEXT("EditorOperationSettingsDescription", "EditorOperation config files."),
		GetMutableDefault<UEditorOperationSetting>()
	);
}

void FEditorOperatorListenerModule::StartupModule()
{

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		RegisterProjectSettings(*SettingsModule);
	}
	

	//todo delete Test codes
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//用户选择的编辑器下的物体发生变化；也可以是世界大纲的，也可以是contentBrowser的
	FEditorDelegates::SelectedProps.AddRaw(this, &FEditorOperatorListenerModule::CB_SelectedProps);

	//用户选择的编辑器下的物体发生变化；也可以是世界大纲的，也可以是contentBrowser的
	USelection::SelectionChangedEvent.AddRaw(this, &FEditorOperatorListenerModule::OnEditorSelectionChanged);


	//编辑器世界：Actor添加到世界绑定；
	GEngine->OnLevelActorAdded().AddRaw(this, &FEditorOperatorListenerModule::OnActorAdded);

	//编辑器世界：Actor删除事件绑定；
	GEngine->OnLevelActorDeleted().AddRaw(this, &FEditorOperatorListenerModule::OnActorDeleted);

	//编辑器世界：Actor移动事件绑定；
	GEngine->OnActorMoved().AddRaw(this, &FEditorOperatorListenerModule::OnActorMoved);
	
	//编辑器世界：多个Actor被移动事件绑定；
	GEngine->OnActorsMoved().AddRaw(this, &FEditorOperatorListenerModule::OnActorsMoved);
	
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");

	//编辑器世界：选中的Actor变化；
	LevelEditorModule.OnElementSelectionChanged().AddRaw(this, &FEditorOperatorListenerModule::OnElementSelectionChanged);

	//覆盖当选中Actor细节面板显示的内容
	LevelEditorModule.OnOverridePropertyEditorSelection().AddRaw(this, &FEditorOperatorListenerModule::OnOverridePropertyEditorSelection);

	//Actor被选中；
	LevelEditorModule.OnActorSelectionChanged().AddRaw(this, &FEditorOperatorListenerModule::OnActorSelectionChanged);

	//获取世界大纲中选中的物体；
	TArray<UObject*> SelectedActors;
	GEditor->GetSelectedActors()->GetSelectedObjects(AActor::StaticClass(), /*out*/ SelectedActors);

	//获取的选中的世界大纲中的Actors；
	TArray<AActor*> SelectedActorsdd;
	
	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActorsdd);



	
}


void FEditorOperatorListenerModule::ShutdownModule()
{
}

void FEditorOperatorListenerModule::CB_SelectedProps()
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte CB_SelectedProps?"))
	//获取世界大纲中选中的物体；
	// TArray<UObject*> SelectedActors;
	// GEditor->GetSelectedActors()->GetSelectedObjects(AActor::StaticClass(), /*out*/ SelectedActors);
}

void FEditorOperatorListenerModule::OnEditorSelectionChanged(UObject* NewSelection)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed OnEditorSelectionChanged?"))
	// TArray<AActor*> SelectedActorsdd;
 // 	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActorsdd);
	//
	// TArray<UObject*> Assets;
	// GEditor->GetSelectedObjects()->GetSelectedObjects<UObject>(Assets);
	//
	// TArray<UObject*> SelectedActorsArray;
	// GEditor->GetSelectedActors()->GetSelectedObjects(UObject::StaticClass(), /*out*/ SelectedActorsArray);
	// if (USelection* SelectedObjects =GEditor->GetSelectedObjects())
	// {
	// 	for ( UObject* Object : Assets )
	// 	{
	// 		if ( SelectedObjects->IsSelected( Object ) )
	// 		{
	// 			SelectedObjects->DeselectAll(  );
	// 		}
	// 	}
	// }
	//
	//
	// if ( USelection* SelectedActors = GEditor->GetSelectedActors() )
	// {
	// 	for ( AActor* Actor : SelectedActorsdd )
	// 	{
	// 		if ( SelectedActors->IsSelected( Actor ) )
	// 		{
	// 			SelectedActors->Deselect( Actor );
	// 		}
	// 	}
	// }
}

void FEditorOperatorListenerModule::OnActorAdded(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Added!"))

}

void FEditorOperatorListenerModule::OnActorMoved(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Moved!"))
	FString UMGPath = UEditorOperationSetting::Get()->GetWidgetInstancePath();
	const FSoftObjectPath BlueprintPath = FSoftObjectPath(UMGPath);
	UObject* BlueprintObject = BlueprintPath.TryLoad();
	UWidgetBlueprint* Blueprint = Cast<UWidgetBlueprint>(BlueprintObject);
	
	if (!Blueprint || Blueprint->IsPendingKillOrUnreachable())
	{
		return;
	}
	
	if (!Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
	{
		return;
	}

	UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
	if (!EditorWidget)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UMG Class name is %s "),*EditorWidget->GetName())
	// UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	// check(EditorWidget);
	// FName TabId;
	// UEditorUtilityWidget* WidgetInstance =EditorUtilitySubsystem->SpawnAndRegisterTabAndGetID(EditorWidget,TabId);
	//
	//
	// if (WidgetInstance && WidgetInstance->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	// {
	// 	IEditorOperationInterface::Execute_OnActorMoved(WidgetInstance,InActor);
	// }

}

void FEditorOperatorListenerModule::OnActorDeleted(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Deleted!"))

}

void FEditorOperatorListenerModule::OnActorsMoved(TArray<AActor*>& InActors)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed OnActorsMoved?"))


}

void FEditorOperatorListenerModule::OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed OnElementSelectionChanged?"))
	//const AActor* Actor = Cast<AActor>(SelectionSet);
	
	// TArray<AActor*> SelectedActorsdd;
	// GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActorsdd);
	//
	// if ( USelection* SelectedActors = GEditor->GetSelectedActors() )
	// {
	// 	for ( AActor* Actor : SelectedActorsdd )
	// 	{
	// 		if ( SelectedActors->IsSelected( Actor ) )
	// 		{
	// 			SelectedActors->Deselect( Actor );
	// 		}
	// 	}
	// }

}

void FEditorOperatorListenerModule::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed OnActorSelectionChanged?"))
}

void FEditorOperatorListenerModule::OnOverridePropertyEditorSelection(const TArray<AActor*>& NewSelection, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed Property selection changed?"))

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorOperatorListenerModule, EditorOperatorPlugin)
