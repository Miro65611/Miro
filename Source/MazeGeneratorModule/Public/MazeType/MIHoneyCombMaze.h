// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeType/MIMazeType.h"
#include "MIHoneyCombMaze.generated.h"

/**
 * 벌집모양 미로
 */
UCLASS(Blueprintable)
class MAZEGENERATORMODULE_API UMIHoneyCombMaze : public UMIMazeType
{
	GENERATED_BODY()

public:
	UMIHoneyCombMaze();

	// MazeType Interface
	virtual void InitializeGraph(FMIGraph& InAdjacencyList) override;
	virtual TTuple<double, double, double, double> GetCoordinateBounds() const override;
	virtual int32 GetVertices() const override;

private:
	static const int32 NeighborDeltas[6][2];

	UPROPERTY(EditAnywhere, Category="Maze", meta=(AllowPrivateAccess="true"))
	int32 Size = 5;
	
	int32 GetVertexIndex(int32 U, int32 V) const;
	bool IsValidNode(int32 U, int32 V) const;
	TPair<int32, int32> GetVCoordinateRange(int32 U) const;
	TTuple<double, double, double, double> GetEdge(int32 U, int32 V, int32 Edge) const;
};
