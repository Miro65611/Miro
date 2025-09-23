// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MICellBorder.h"
#include "MIMaze.generated.h"

class UMIMazeAlgorithm;

/**
 * �̷��� �⺻ Ŭ����
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
	FMIGraph AdjacencyList; // ��������Ʈ
	FMIGraph Solution; 
	int32 StartVertex;
	int32 EndVertex;

	void RemoveBorders(const TArray<TPair<int32, int32>>& Edges);
	virtual TTuple<double, double, double, double> GetCoordinateBounds()const;
};
