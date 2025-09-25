// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Algorithm/MIMazeAlgorithm.h"
#include "MIBreadFirstSearch.generated.h"

/**
 *  BFS
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIBreadFirstSearch : public UMIMazeAlgorithm
{
	GENERATED_BODY()

public:
	UMIBreadFirstSearch();
	
	virtual FMISpanningTree GenerateSpanningTree(const int32 Vertices, const FMIGraph& AdjacencyList) override;

private:
	TArray<bool> Visited;
	TArray<int32> CurrentLevel;
	TArray<int32> NextLevel;
};
