// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MIMazeGenerationData.generated.h"

class UMIMazeType;
class UMIMazeAlgorithm;
  
/**
 * 미로 생성 데이터 
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeGenerationData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	TSubclassOf<UMIMazeType> MazeTypeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	TSubclassOf<UMIMazeAlgorithm> MazeAlgorithmClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	int32 StartVertex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	int32 EndVertex;

	
};
