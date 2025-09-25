// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeType/MICircularMaze.h"

#include <ThirdParty/hlslcc/hlslcc/src/hlslcc_lib/compiler.h>


TTuple<double, double, double, double> UMICircularMaze::GetCoordinateBounds() const
{
	return MakeTuple(-NumberOfRing, -NumberOfRing, NumberOfRing, NumberOfRing);
}

int32 UMICircularMaze::GetVertices() const
{
	return RingNodeCount.Top() + RingNodePrefixSum.Top();
}

void UMICircularMaze::PostInitProperties()
{
	Super::PostInitProperties();

	InitializeRing();
}

void UMICircularMaze::InitializeRing()
{
	RingNodeCount.Init(0, NumberOfRing);
	RingNodePrefixSum.Init(0, NumberOfRing);

	RingNodeCount[0] = 1;
	RingNodePrefixSum[0] = 0;

	for (int32 Index = 1; Index < NumberOfRing; Index++)
	{
		RingNodeCount[Index] = RingNodeCount[Index - 1];

		if (2 * M_PI * Index / RingNodeCount[Index - 1] > 2)
		{
			RingNodeCount[Index] *= 2;
		}
		RingNodePrefixSum[Index] = RingNodePrefixSum[Index - 1] + RingNodeCount[Index - 1];
	}
}

void UMICircularMaze::InitializeGraph(FMIGraph& InAdjacencyList)
{
	Super::InitializeGraph(InAdjacencyList);

	// 링 정보 초기화
	InitializeRing();

	InAdjacencyList.SetNum(GetVertices());

	for (int32 I = 1; I < NumberOfRing; I++)
	{
		for (int J = 0; J < RingNodeCount[I]; J++)
		{
			int32 CurrentNodeIndex = RingNodePrefixSum[I] + J;
			TSharedPtr<FMICellBorder> Ptr = nullptr;

			int32 TargetNodeIndex = RingNodePrefixSum[I - 1] + (RingNodeCount[I - 1] * J) / RingNodeCount[I];

			Ptr = MakeShared<FMIArcBorder>(0, 0, I, J * 2 * M_PI / RingNodeCount[I] - M_PI / 2,
			                               (J + 1) * 2 * M_PI / RingNodeCount[I] - M_PI / 2);

			InAdjacencyList[CurrentNodeIndex].Add({TargetNodeIndex, Ptr});
			InAdjacencyList[TargetNodeIndex].Add({CurrentNodeIndex, Ptr});

			TargetNodeIndex = RingNodePrefixSum[I] + ((J + 1) % RingNodeCount[I]);
			const double Theta = (J + 1) * 2 * M_PI / RingNodeCount[I] - M_PI / 2;

			Ptr = MakeShared<FMILineBorder>(I * FMath::Cos(Theta), I * FMath::Sin(Theta),
			                                (I + 1) * FMath::Cos(Theta), (I + 1) * FMath::Sin(Theta));

			InAdjacencyList[CurrentNodeIndex].Add({TargetNodeIndex, Ptr});
			InAdjacencyList[TargetNodeIndex].Add({CurrentNodeIndex, Ptr});

			// 가장자리 원
			if (I == NumberOfRing - 1)
			{
				Ptr = MakeShared<FMIArcBorder>(0, 0, NumberOfRing, J * 2 * M_PI / RingNodeCount[I] - M_PI / 2,
				                               (J + 1) * 2 * M_PI / RingNodeCount[I] - M_PI / 2);
				InAdjacencyList[CurrentNodeIndex].Add({-1, Ptr});
			}
		}
	}
}
