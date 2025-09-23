// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MIMazeGenerator.generated.h"

class UMIMaze;
class UMIMazeAlgorithm;

/**
 * 미로 생성기 클래스
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeGenerator : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeGenerator();
	void GenerateMaze();
	UMIMaze* GetMaze()const { return Maze.Get(); }


private:
	UPROPERTY()
	TObjectPtr<UMIMaze> Maze;

	UPROPERTY()
	TObjectPtr<UMIMazeAlgorithm> MazeAlgorithm;
};
