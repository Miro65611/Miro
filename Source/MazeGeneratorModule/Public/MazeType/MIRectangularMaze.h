// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeType/MIMazeType.h"
#include "MIRectangularMaze.generated.h"

/**
 * 사각형 모양 미로 
 */
UCLASS(Blueprintable)
class MAZEGENERATORMODULE_API UMIRectangularMaze : public UMIMazeType
{
	GENERATED_BODY()

public:
	UMIRectangularMaze();
	
	virtual void PostInitProperties() override;
	
	virtual void InitializeGraph(FMIGraph& InAdjacencyList) override;

	virtual int32 GetVertices() const override; 
	
private:
	UPROPERTY(EditAnywhere, Category="Maze", meta=(AllowPrivateAccess="true"))
	int32 Width;

	UPROPERTY(EditAnywhere, Category="Maze", meta=(AllowPrivateAccess="true"))
	int32 Height;
	
	int32 GetVertexIndex(const int32 Row, const int32 Column) const;

	virtual TTuple<double, double, double, double> GetCoordinateBounds() const override;
};
