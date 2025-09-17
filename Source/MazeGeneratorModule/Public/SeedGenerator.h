// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeStruct.h"
#include "SeedGenerator.generated.h"

/**
 * 시드생성을 담당한다
 */
UCLASS()
class MAZEGENERATORMODULE_API USeedGenerator : public UObject
{
	GENERATED_BODY()

public:
	USeedGenerator();

	FSeed GenerateSeed();
};
