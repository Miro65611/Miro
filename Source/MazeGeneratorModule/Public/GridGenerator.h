// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeStruct.h"
#include "Math/RandomStream.h"
#include "GridGenerator.generated.h"


/**
 * �׸��� ������ ��� 
 */
UCLASS()
class MAZEGENERATORMODULE_API UGridGenerator : public UObject
{
	GENERATED_BODY()

public:
	UGridGenerator();
	UGridGenerator(FSeed InSeed);

	FGrid GernerateGridData(uint32 Width, uint32 Height) const;

private:
	FSeed Seed;
	FRandomStream RandomStream;
}; 
