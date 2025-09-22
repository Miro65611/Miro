// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMazeEditorModule : public IModuleInterface
{
public:
    /**
     * 모듈이 로드될 때 호출됩니다.
     */
    virtual void StartupModule() override;


    /**
     * 모듈이 언로드될 때 호출됩니다.
     */
    virtual void ShutdownModule() override;

    void RegisterMenus();

    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
};

