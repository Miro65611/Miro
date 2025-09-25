// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeType/MIMazeType.h"
#include "MITriangularMaze.generated.h"

/**
 * 삼각형모양 
 */
UCLASS(Blueprintable)
class MAZEGENERATORMODULE_API UMITriangularMaze : public UMIMazeType
{
	GENERATED_BODY()

public:
	UMITriangularMaze();

	virtual void InitializeGraph(FMIGraph& InAdjacencyList) override;

	virtual TTuple<double, double, double, double> GetCoordinateBounds() const override;

	virtual int32 GetVertices() const override; 
	
private:
	UPROPERTY(EditAnywhere, Category="Maze", meta=(AllowPrivateAccess="true"))
	int32 Rows = 10;

	// Get vertex index for a cell at (row, col)
	int32 GetVertexIndex(const int32 Row, const int32 Col) const;

	// Get number of cells in a given row
	int32 GetCellsInRow(const int32 Row) const;

	// Get total number of cells up to (but not including) a given row
	int32 GetCellsBeforeRow(const int Row) const;
};
