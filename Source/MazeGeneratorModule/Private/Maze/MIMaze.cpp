// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/MIMaze.h"
#include "Algorithm//MIMazeAlgorithm.h"

UMIMaze::UMIMaze()
	:Vertices(0)
	, AdjacencyList{}
	, Solution{}
	, StartVertex(0)
	, EndVertex(0)
{
}

void UMIMaze::InitializeGraph()
{
	AdjacencyList.Reset();
	AdjacencyList.SetNum(Vertices);
}

void UMIMaze::GenerateMaze(UMIMazeAlgorithm* Algorithm)
{
	FMISpanningTree SpannigTree = Algorithm->GenerateSpannigTree(Vertices, AdjacencyList);

	// Solve(SpannigTree);

	RemoveBorders(SpannigTree);
}

void UMIMaze::RemoveBorders(const TArray<TPair<int32, int32>>& Edges)
{
	for (const auto& [U, V] : Edges)
	{
		AdjacencyList[U].RemoveAll([V](const FMIEdge& InEdge)
			{
				return InEdge.Get<0>() == V;
			});

		AdjacencyList[V].RemoveAll([U](const FMIEdge& InEdge)
			{
				return InEdge.Get<0>() == U;
			});
	}
}

TTuple<double, double, double, double> UMIMaze::GetCoordinateBounds() const
{
	return TTuple<double, double, double, double>();
}
