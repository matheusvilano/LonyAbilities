// © Lony Studios / Matheus Vilano

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class LONYABILITIES_API FLonyAbilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
