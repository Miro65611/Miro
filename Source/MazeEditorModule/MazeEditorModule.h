// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMazeEditorModule : public IModuleInterface
{
public:
	/**
	 * Module이 시작할때 호출  
	 */
	virtual void StartupModule() override;


	/**
	 * Module이 끝날 때 호출
	 */
	virtual void ShutdownModule() override;

	void RegisterMenus();

	TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
};
