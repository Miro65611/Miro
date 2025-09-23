// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MICellBorder.h"
#include "MIMazeType.generated.h"

/**
 * 미로 형태를 추상화
 */
UCLASS(Abstract)
class MAZEGENERATORMODULE_API UMIMazeType : public UObject
{
	GENERATED_BODY()
	
public:
	UMIMazeType();

	virtual void InitializeGraph(FMIGraph& InAdjacencyList);
	virtual TTuple<double, double, double, double> GetCoordinateBounds()const;

	virtual int32 GetVertices() const { return 0; }
	
protected:
	int32 StartVertex;
	int32 EndVertex;

};
