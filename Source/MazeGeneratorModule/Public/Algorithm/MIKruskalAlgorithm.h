// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Algorithm/MIMazeAlgorithm.h"
#include "MIKruskalAlgorithm.generated.h"

/**
 * 크루스칼 알고리즘
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIKruskalAlgorithm : public UMIMazeAlgorithm
{
	GENERATED_BODY()
	
public:
	UMIKruskalAlgorithm();
	virtual FMISpanningTree GenerateSpannigTree(int32 Vertices, const FMIGraph& InGraph) override;

private:
	TArray<int32> Parent;
	int32 GetParent(int32 U);
};
