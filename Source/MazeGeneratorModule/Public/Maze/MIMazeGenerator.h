// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MIMazeGenerator.generated.h"

class UMIMaze;
class UMIMazeAlgorithm;

/**
 * �̷� ������ Ŭ����
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeGenerator : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeGenerator();

	void GenerateMaze();

private:
	UPROPERTY()
	TObjectPtr<UMIMaze> Maze;

	UPROPERTY()
	TObjectPtr<UMIMazeAlgorithm> MazeAlgorithm;
};
