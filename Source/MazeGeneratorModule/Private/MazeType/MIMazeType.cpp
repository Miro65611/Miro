// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeType/MIMazeType.h"
#include "Algorithm/MIMazeAlgorithm.h"

UMIMazeType::UMIMazeType()
	: StartVertex(0)
	  , EndVertex(0)
{
}

void UMIMazeType::InitializeGraph(FMIGraph& InAdjacencyList)
{
	InAdjacencyList.Reset();
}


TTuple<double, double, double, double> UMIMazeType::GetCoordinateBounds() const
{
	return TTuple<double, double, double, double>();
}

void UMIMazeType::SetStartEndVertex(const int32 InStartVertex, const int32 InEndVertex)
{
	StartVertex = InStartVertex;
	EndVertex = InEndVertex;
}
