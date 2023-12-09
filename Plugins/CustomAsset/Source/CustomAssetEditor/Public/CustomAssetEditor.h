#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class IAssetTypeActions;

class FCustomAssetEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<IAssetTypeActions> Action ;
};
