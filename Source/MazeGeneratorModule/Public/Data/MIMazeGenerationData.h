// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MIMazeGenerationData.generated.h"

class UMIMaze;
class UMIMazeAlgorithm;

/**
 * �̷� ���� ������ 
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeGenerationData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	TSubclassOf<UMIMaze> MazeType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	TSubclassOf<UMIMazeAlgorithm> MazeAlgorithm;
};
