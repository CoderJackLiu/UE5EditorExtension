// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEditorOperatorPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void CB_SelectedProps();
	void OnEditorSelectionChanged(UObject* NewSelection);

	void OnActorChangedSomehow(AActor* InActor);
	void OnActorsChangedSomehow(TArray<AActor*>& InActors);	

	/** Called when element selection changes */
	void OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh = false);

	/** Called when actor selection changes */
	void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);


};
