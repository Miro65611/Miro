// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MICellBorder.h"
#include "MIMazeAlgorithm.generated.h"

/**
 * �̷� �˰����� Ŭ���� 
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeAlgorithm : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeAlgorithm();

	void SetRandomStream(const TSharedPtr<FRandomStream> InRandomStream);
	virtual FMISpanningTree GenerateSpannigTree(int32 Vertices, const FMIGraph& InGraph);

protected:
	FMISpanningTree SpanningTree;
	TSharedPtr<FRandomStream> RandomStream;
};
