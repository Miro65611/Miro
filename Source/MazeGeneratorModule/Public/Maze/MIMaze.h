// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MICellBorder.h"
#include "MIMaze.generated.h"

class UMIMazeAlgorithm;

/**
 * 미로의 기본 클래스
 */
UCLASS(Abstract)
class MAZEGENERATORMODULE_API UMIMaze : public UObject
{
	GENERATED_BODY()
	
public:
	UMIMaze();

	virtual void InitializeGraph();
	
	void GenerateMaze(UMIMazeAlgorithm* Algorithm);

	const FMIGraph& GetAdjacencyList()const { return AdjacencyList; }
	const FMIGraph& GetSolution()const { return Solution; }

protected:
	int32 Vertices;
	FMIGraph AdjacencyList; // 인접리스트
	FMIGraph Solution; 
	int32 StartVertex;
	int32 EndVertex;

	void RemoveBorders(const TArray<TPair<int32, int32>>& Edges);
	virtual TTuple<double, double, double, double> GetCoordinateBounds()const;
};
