// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeType/MIMazeType.h"
#include "MICircularMaze.generated.h"

/**
 * Circular Type
 */
UCLASS()
class MAZEGENERATORMODULE_API UMICircularMaze : public UMIMazeType
{
	GENERATED_BODY()

public:
	virtual void InitializeGraph(FMIGraph& InAdjacencyList) override;
	virtual TTuple<double, double, double, double> GetCoordinateBounds() const override;
	virtual int32 GetVertices() const override; 

	// Ring개수에 따라서 초기화
	virtual void PostInitProperties() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Maze", meta=(AllowPrivateAccess="true"))
	int32 NumberOfRing;
	
	TArray<int32> RingNodeCount;
	TArray<int32> RingNodePrefixSum;

	void InitializeRing();
};
