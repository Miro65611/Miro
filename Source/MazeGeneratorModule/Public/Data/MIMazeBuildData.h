// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MIMazeBuildData.generated.h"

class AMILineBorder;
class AMIArcBorder;
/**
 * 미로 빌드 데이터
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeBuildData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Maze")
	TSubclassOf<AMIArcBorder> ArcBorderClass;

	UPROPERTY(EditAnywhere, Category = "Maze")
	TSubclassOf<AMILineBorder> LineBorderClass;
	
	UPROPERTY(EditAnywhere, Category = "Maze")
	FVector MazeWorldOffset;
	
	UPROPERTY(EditAnywhere, Category = "Maze")
	double  MazeToWorldScale;
};
