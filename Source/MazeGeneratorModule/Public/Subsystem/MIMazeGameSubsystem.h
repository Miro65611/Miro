// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MIMazeGameSubsystem.generated.h"


class UMIMazeBuildData;
class UMIMazeGenerator;
class UMIMazeBuilder;
class UMIMazeGenerationData;

  /**
 * Game에서 Maze를 전체적으로 관리하는 매니저
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMIMazeGameSubsystem();

	
	void InitializeMaze(int32 InSeed);

	
private:
	UPROPERTY()
	TObjectPtr<UMIMazeBuilder> MazeBuilder;

	UPROPERTY()
	TObjectPtr<UMIMazeGenerator> MazeGenerator;

	UPROPERTY()
	TObjectPtr<UMIMazeGenerationData> MazeGenerateData;

	UPROPERTY()
	TObjectPtr<UMIMazeBuildData> MazeBuildData;

	int32 Seed;

	TSharedPtr<FRandomStream> RandomStream;
	
};
