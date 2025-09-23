// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MIMazeSubsystem.generated.h"

class UMIMazeGenerationData;

/**
 *  MazeSubsystem
 */
UCLASS()
class MAZEEDITORMODULE_API UMIMazeSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:    
    // 초기화 시점 (에디터 실행 시)
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // 종료 시점 (에디터 닫힐 때)
    virtual void Deinitialize() override;


private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMIMazeGenerationData> MazeGenerationData;
    



};
