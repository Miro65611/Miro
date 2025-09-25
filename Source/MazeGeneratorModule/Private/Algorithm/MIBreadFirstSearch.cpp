// Fill out your copyright notice in the Description page of Project Settings.


#include "Algorithm/MIBreadFirstSearch.h"
#include "Maze/MIRandomHelper.h"

UMIBreadFirstSearch::UMIBreadFirstSearch()
{
}

FMISpanningTree UMIBreadFirstSearch::GenerateSpanningTree(const int32 Vertices, const FMIGraph& AdjacencyList)
{
	Visited.Init(false, Vertices);

	const int StartVertex = RandomStream->RandRange(0, Vertices - 1);
	CurrentLevel.Add(StartVertex);
	Visited[StartVertex] = true;

	SpanningTree.Reset();

	while (!CurrentLevel.IsEmpty())
	{
		for (const int32 Vertex : CurrentLevel)
		{
			for (const FMIEdge& Edge : AdjacencyList[Vertex])
			{
				int32 NextVertex = Edge.Get<0>();
				if (NextVertex < 0 or Visited[NextVertex])
				{
					continue;
				}

				Visited[NextVertex] = true;
				SpanningTree.Add({Vertex, NextVertex});
				NextLevel.Add(NextVertex);
			}
		}

		CurrentLevel.Reset();
		Swap(CurrentLevel, NextLevel);
		MiroRandomHelper::ShuffleWithStream(CurrentLevel, *RandomStream);
	}


	return SpanningTree;
}
