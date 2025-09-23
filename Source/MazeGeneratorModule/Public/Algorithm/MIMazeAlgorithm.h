// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MICellBorder.h"
#include "MIMazeAlgorithm.generated.h"

/**
 * 미로 알고리즘 
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeAlgorithm : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeAlgorithm();

	void SetRandomStream(const TSharedPtr<FRandomStream>& InRandomStream);

	virtual FMISpanningTree GenerateSpanningTree(const int32 Vertices, const FMIGraph& InGraph);



protected:
	FMISpanningTree SpanningTree;
	TSharedPtr<FRandomStream> RandomStream;
};
