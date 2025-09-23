// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Algorithm/MIMazeAlgorithm.h"
#include "MIDepthFirstSearch.generated.h"

/**
 * DFS - Recursive Backtracking
 * 
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIDepthFirstSearch : public UMIMazeAlgorithm
{
	GENERATED_BODY()

public:
	UMIDepthFirstSearch();
	
	virtual FMISpanningTree GenerateSpanningTree(const int32 Vertices, const FMIGraph& InGraph) override;

protected:
	TArray<int32> Parent;
	void DepthFirstSearch(const int32, const FMIGraph& AdjacencyList);
};
