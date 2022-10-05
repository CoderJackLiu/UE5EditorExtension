// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorOperatorListener.h"

#include "Selection.h"
#include "Editor.h"
#include "EditorOperationInterface.h"
#include "EditorOperationSetting.h"
#include "EditorOperationSubsystem.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "WidgetBlueprint.h"
#include "UObject/ConstructorHelpers.h"
#define LOCTEXT_NAMESPACE "FEditorOperatorPluginModule"

UEditorUtilityWidget* FEditorOperatorListenerModule::WidgetInstance = nullptr;
bool FEditorOperatorListenerModule::bMapHasOpened = false;

FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");


void RegisterProjectSettings(ISettingsModule& SettingsModule)
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
	//注册projectSetting，扩展编辑器上的面板
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		RegisterProjectSettings(*SettingsModule);
	}

	BindingEditorWorldOperations();

	
	//用户选择的编辑器下的物体发生变化；也可以是世界大纲的，也可以是contentBrowser的
	USelection::SelectionChangedEvent.AddRaw(this, &FEditorOperatorListenerModule::OnEditorSelectionChanged);
	
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

	//todo  restart the unreal editor
	FUnrealEdMisc::Get().RestartEditor(false);
	
}

void FEditorOperatorListenerModule::BindingEditorWorldOperations()
{
	{
		//编辑器世界：Actor添加到世界绑定；
		GEngine->OnLevelActorAdded().AddRaw(this, &FEditorOperatorListenerModule::OnActorAdded);

		//编辑器世界：Actor删除事件绑定；
		GEngine->OnLevelActorDeleted().AddRaw(this, &FEditorOperatorListenerModule::OnActorDeleted);

		//编辑器世界：Actor移动事件绑定；
		GEngine->OnActorMoved().AddRaw(this, &FEditorOperatorListenerModule::OnActorMoved);

		//编辑器世界：选中的Actor变化；
		LevelEditorModule.OnElementSelectionChanged().AddRaw(this, &FEditorOperatorListenerModule::OnElementSelectionChanged);

		//覆盖当选中Actor细节面板显示的内容
		LevelEditorModule.OnOverridePropertyEditorSelection().AddRaw(this, &FEditorOperatorListenerModule::OnOverridePropertyEditorSelection);

		//编辑器世界：选中的Actor变化；
		LevelEditorModule.OnActorSelectionChanged().AddRaw(this, &FEditorOperatorListenerModule::OnActorSelectionChanged);

		//用户选择的编辑器下的物体发生变化；也可以是世界大纲的，也可以是contentBrowser的
		FEditorDelegates::SelectedProps.AddRaw(this, &FEditorOperatorListenerModule::CB_SelectedProps);

	}
	

	//关卡事件
	{
		//关卡跳转
		LevelEditorModule.OnMapChanged().AddRaw(this, &FEditorOperatorListenerModule::OnMapChanged);

		//关卡被打开
		FEditorDelegates::OnMapOpened.AddRaw(this, &FEditorOperatorListenerModule::OnMapOpened);
		
	}

	{
		//Tab Content 被修改
		LevelEditorModule.OnTabContentChanged().AddRaw(this, &FEditorOperatorListenerModule::OnTabContentChanged);

		//编辑器界面创建完毕
		LevelEditorModule.OnLevelEditorCreated().AddRaw(this, &FEditorOperatorListenerModule::OnLevelEditorCreated);

		//刷新画面
		LevelEditorModule.OnRedrawLevelEditingViewports().AddRaw(this, &FEditorOperatorListenerModule::OnRedrawLevelEditingViewports);

		//组件被编辑
		LevelEditorModule.OnComponentsEdited().AddRaw(this, &FEditorOperatorListenerModule::OnComponentsEditedInWorld);

		//截图事件
		LevelEditorModule.OnTakeHighResScreenShots().AddRaw(this, &FEditorOperatorListenerModule::TakeHighResScreenShot);

	}

}

void FEditorOperatorListenerModule::OnEditorSelectionChanged(UObject* NewSelection)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed OnEditorSelectionChanged?"))
	TArray<AActor*> SelectedActorsdd;
	GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActorsdd);
	
}

void FEditorOperatorListenerModule::OnActorAdded(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Added!"))

	if (bMapHasOpened && GetWidgetInstance() && GetWidgetInstance()->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	{
		IEditorOperationInterface::Execute_OnActorAdded(GetWidgetInstance(), InActor);
	}
}

void FEditorOperatorListenerModule::OnActorMoved(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Moved!"))
	if (bMapHasOpened && GetWidgetInstance() && GetWidgetInstance()->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	{
		IEditorOperationInterface::Execute_OnActorMoved(GetWidgetInstance(), InActor);
	}
}

void FEditorOperatorListenerModule::OnActorDeleted(AActor* InActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Deleted!"))
	if (bMapHasOpened && GetWidgetInstance() && GetWidgetInstance()->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	{
		IEditorOperationInterface::Execute_OnActorDeleted(GetWidgetInstance(), InActor);
	}
}

void FEditorOperatorListenerModule::OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Editor world Selecte changed OnElementSelectionChanged?"))
	if (bMapHasOpened && GetWidgetInstance() && GetWidgetInstance()->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	{
		IEditorOperationInterface::Execute_OnElementSelectionChanged(GetWidgetInstance(), SelectionSet,bForceRefresh);
	}
}

void FEditorOperatorListenerModule::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed OnActorSelectionChanged?"))
	if (bMapHasOpened && GetWidgetInstance() && GetWidgetInstance()->GetClass()->ImplementsInterface(UEditorOperationInterface::StaticClass()))
	{
		IEditorOperationInterface::Execute_OnActorSelectionChanged(GetWidgetInstance(), NewSelection,bForceRefresh);
	}
}

void FEditorOperatorListenerModule::OnOverridePropertyEditorSelection(const TArray<AActor*>& NewSelection, bool bForceRefresh)
{
	UE_LOG(LogTemp, Warning, TEXT("Selecte changed Property selection changed?"))
}

void FEditorOperatorListenerModule::OnMapChanged(UWorld* World, EMapChangeType MapChangeType)
{
}

void FEditorOperatorListenerModule::OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor)
{
	
}

void FEditorOperatorListenerModule::OnRedrawLevelEditingViewports(bool bInvalidateHitProxies)
{
}

void FEditorOperatorListenerModule::OnTabContentChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("OnTabContentChanged"))

}

void FEditorOperatorListenerModule::OnComponentsEditedInWorld()
{
	
}

void FEditorOperatorListenerModule::TakeHighResScreenShot()
{
	
}

void FEditorOperatorListenerModule::OnMapOpened(const FString& Filename, bool bLoadAsTemplate)
{
	UE_LOG(LogTemp, Warning, TEXT("MapOpened"))
	bMapHasOpened = true;
}

UEditorUtilityWidget* FEditorOperatorListenerModule::GetWidgetInstance() const
{
	if (!WidgetInstance->IsValidLowLevel())
	{
		FString UMGPath = UEditorOperationSetting::Get()->GetWidgetInstancePath();
		const FSoftObjectPath BlueprintPath = FSoftObjectPath(UMGPath);
		UObject* BlueprintObject = BlueprintPath.TryLoad();
		UWidgetBlueprint* Blueprint = Cast<UWidgetBlueprint>(BlueprintObject);

		if (!Blueprint || IsValid(Blueprint))
		{
			return nullptr;
		}

		if (!Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
		{
			return nullptr;
		}

		UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
		if (!EditorWidget)
		{
			return nullptr;
		}
		UE_LOG(LogTemp, Warning, TEXT("Creating UMG Class name is %s "), *EditorWidget->GetName())
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		check(EditorWidget);
		FName TabId;
		WidgetInstance = EditorUtilitySubsystem->SpawnAndRegisterTabAndGetID(EditorWidget, TabId);
	}
	return WidgetInstance;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorOperatorListenerModule, EditorOperatorPlugin)
