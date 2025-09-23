// Fill out your copyright notice in the Description page of Project Settings.


#include "Algorithm/MIKruskalAlgorithm.h"
#include "Maze/MIRandomHelper.h"

UMIKruskalAlgorithm::UMIKruskalAlgorithm()
{
}

FMISpanningTree UMIKruskalAlgorithm::GenerateSpanningTree(const int32 Vertices, const FMIGraph& AdjacencyList)
{
	TArray<TPair<int32, int32>> Edges;

	// 모든 간선(벽 정보를 가져온다)
	for (int Index = 0; Index < Vertices; ++Index)
	{
		for (const FMIEdge& Edge : AdjacencyList[Index])
		{
			if (Edge.Get<0>() > Index)
			{
				Edges.Add({Index, Edge.Get<0>()});
			}
		}
	}

	MiroRandomHelper::ShuffleWithStream(Edges, *RandomStream);

	// 집합초기화
	Parent.Empty();
	for (int32 Index = 0; Index < Vertices; ++Index)
	{
		Parent.Add(Index);
	}

	SpanningTree.Reset();


	for (const TPair<int32, int32>& Edge : Edges)
	{
		int32 U = GetParent(Edge.Get<0>());
		int32 V = GetParent(Edge.Get<1>());
		if (U == V)
		{
			continue;
		}

		Parent[U] = V;
		SpanningTree.Add(Edge);
	}

	return SpanningTree;
}

int32 UMIKruskalAlgorithm::GetParent(int32 U)
{
	return (Parent[U] == U) ? U : (Parent[U] = GetParent(Parent[U]));
}
