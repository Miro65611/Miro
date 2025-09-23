// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/MIMazeGenerator.h"
#include "MazeType/MIMazeType.h"
#include "Algorithm/MIMazeAlgorithm.h"
#include "Data/MIMazeGenerationData.h"
#include "MazeGeneratorModule/MazeGeneratorModule.h"

UMIMazeGenerator::UMIMazeGenerator()
	: MazeType(nullptr)
	  , MazeAlgorithm(nullptr)
{
}

UMIMazeGenerator::UMIMazeGenerator(UMIMazeType* MazeType, UMIMazeAlgorithm* MazeAlgorithm)
	: MazeType(MazeType), MazeAlgorithm(MazeAlgorithm)
{
}

void UMIMazeGenerator::SetRandomStream(const TSharedPtr<FRandomStream>& InRandomStream)
{
	RandomStream = InRandomStream;
	 MazeAlgorithm->SetRandomStream(InRandomStream);
}

void UMIMazeGenerator::InitializeMaze(const UMIMazeGenerationData* MazeGenerationData)
{
	MazeType = NewObject<UMIMazeType>(this, MazeGenerationData->MazeTypeClass);
	if (MazeType == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MazeType is nullptr"));
	}

	MazeAlgorithm = NewObject<UMIMazeAlgorithm>(this, MazeGenerationData->MazeAlgorithmClass);
	if (MazeAlgorithm == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MazeAlgorithm is nullptr"));
	}

	StartVertex = MazeGenerationData->StartVertex;
	EndVertex = MazeGenerationData->EndVertex;

	Vertices = MazeType->GetVertices();
}

void UMIMazeGenerator::GenerateMaze()
{
	if (MazeType == nullptr)
	{
		UE_LOG(LogMazeModule, Warning, TEXT("MazeGenerator : MazeType is nullptr"));
		return;
	}

	if (MazeAlgorithm == nullptr)
	{
		UE_LOG(LogMazeModule, Warning, TEXT("MazeGenerator : MazeAlgorithm is nullptr"));
		return;
	}

	MazeType->InitializeGraph(AdjacencyList);

	const FMISpanningTree SpanningTree = MazeAlgorithm->GenerateSpanningTree(Vertices, AdjacencyList);

	RemoveBorders(SpanningTree);
}

void UMIMazeGenerator::RemoveBorders(const TArray<TPair<int32, int32>>& Edges)
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
