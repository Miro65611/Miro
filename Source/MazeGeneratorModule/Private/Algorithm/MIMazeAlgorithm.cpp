// Fill out your copyright notice in the Description page of Project Settings.


#include "Algorithm/MIMazeAlgorithm.h"
#include "MazeGeneratorModule/MazeGeneratorModule.h"

UMIMazeAlgorithm::UMIMazeAlgorithm()
	:SpanningTree{}
	,RandomStream(nullptr)
{
}

void UMIMazeAlgorithm::SetRandomStream(const TSharedPtr<FRandomStream>& InRandomStream)
{
	RandomStream = InRandomStream;
}

FMISpanningTree UMIMazeAlgorithm::GenerateSpanningTree(const int32 Vertices, const FMIGraph& AdjacencyList)
{
	return SpanningTree;
}
