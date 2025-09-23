// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MIMazeSubsystem.generated.h"

class UMIMazeGenerator;
class UMIMazeGenerationData;

/**
 *  MazeSubsystem
 */
UCLASS()
class MAZEEDITORMODULE_API UMIMazeSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UMIMazeSubsystem();
	
	// Subsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UMIMazeGenerator* GetMazeGenerator();
	UMIMazeGenerationData* GetMazeGenerationData();

	void SetMazeGeneratorData(UMIMazeGenerationData* Data);

	void SetRandomStream(int32 InSeed = 0);
	
private:
	UPROPERTY()
	TObjectPtr<UMIMazeGenerator> MazeGenerator;

	UPROPERTY()
	TObjectPtr<UMIMazeGenerationData> MazeGenerationData;

	TSharedPtr<FRandomStream> RandomStream;

	int32 Seed;
};
