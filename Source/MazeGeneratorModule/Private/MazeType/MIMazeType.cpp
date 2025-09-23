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
}


TTuple<double, double, double, double> UMIMazeType::GetCoordinateBounds() const
{
	return TTuple<double, double, double, double>();
}
