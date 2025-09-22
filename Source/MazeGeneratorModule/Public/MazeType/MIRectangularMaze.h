// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MIMaze.h"
#include "MIRectangularMaze.generated.h"

/**
 * 정사각형 모양 미로
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIRectangularMaze : public UMIMaze
{
	GENERATED_BODY()

public:
	UMIRectangularMaze();

	virtual void InitializeGraph()override;

private:
	int32 Width;
	int32 Height;
	int32 GetVertexIndex(int32 Row, int32 Column) const;

	virtual TTuple<double, double, double, double> GetCoordinateBounds()const override;
};

