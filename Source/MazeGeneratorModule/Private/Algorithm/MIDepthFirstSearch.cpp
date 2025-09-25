// Fill out your copyright notice in the Description page of Project Settings.


#include "Algorithm/MIDepthFirstSearch.h"
#include  "Maze/MIRandomHelper.h"

UMIDepthFirstSearch::UMIDepthFirstSearch()
{
}

FMISpanningTree UMIDepthFirstSearch::GenerateSpanningTree(const int32 Vertices, const FMIGraph& AdjacencyList)
{
	SpanningTree.Reset();

	Parent.Empty();
	Parent.Init(-1, Vertices);

	DepthFirstSearch(RandomStream->RandRange(0, Vertices - 1), AdjacencyList);
	
	return SpanningTree;
}

void UMIDepthFirstSearch::DepthFirstSearch(const int32 Vertex, const FMIGraph& AdjacencyList) 
{
	TArray<int32> NodeOrder;

	for (int32 Index =0; Index <  AdjacencyList[Vertex].Num(); Index++)
	{
		NodeOrder.Add(Index);		
	}

	MiroRandomHelper::ShuffleWithStream(NodeOrder, *RandomStream);

	for (const int32 Index : NodeOrder)
	{
		int NextVertex = AdjacencyList[Vertex][Index].Get<0>();

		// 살다살다 or 라는 키워드가 있을줄은 몰랐네
		if (NextVertex < 0 or  Parent[NextVertex] >= 0)
		{
			continue;
		}

		SpanningTree.Add({Vertex, NextVertex});
		Parent[NextVertex] = Vertex;
		DepthFirstSearch(NextVertex, AdjacencyList);
	}
}
