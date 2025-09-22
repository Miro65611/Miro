// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMazeEditorModule : public IModuleInterface
{
public:
    /**
     * ����� �ε�� �� ȣ��˴ϴ�.
     */
    virtual void StartupModule() override;


    /**
     * ����� ��ε�� �� ȣ��˴ϴ�.
     */
    virtual void ShutdownModule() override;

    void RegisterMenus();

    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
};

