// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeType/MIRectangularMaze.h"


UMIRectangularMaze::UMIRectangularMaze()
{
}

void UMIRectangularMaze::InitializeGraph(FMIGraph& InAdjacencyList)
{
	Super::InitializeGraph(InAdjacencyList);
	
	FMIGraph& AdjacencyList = InAdjacencyList;

	AdjacencyList.SetNum(Width * Height);

	// 상하 벽
	for (int32 Column = 0; Column < Width; ++Column)
	{
		AdjacencyList[GetVertexIndex(0, Column)].Add(
			FMIEdge(-1, MakeShared<FMILineBorder>(Column, 0, Column + 1, 0)));
		AdjacencyList[GetVertexIndex(Height - 1, Column)].Add(
			FMIEdge(-1, MakeShared<FMILineBorder>(Column, Height, Column + 1, Height)));
	}

	// 좌우 벽
	for (int32 Row = 0; Row < Height; ++Row)
	{
		AdjacencyList[GetVertexIndex(Row, 0)].Add(FMIEdge(-1, MakeShared<FMILineBorder>(0, Row, 0, Row + 1)));
		AdjacencyList[GetVertexIndex(Row, Width - 1)].Add(
			FMIEdge(-1, MakeShared<FMILineBorder>(Width, Row, Width, Row + 1)));
	}
	
	for (int32 Row = 0; Row < Height; ++Row)
	{
		for (int32 Column = 0; Column < Width - 1; ++Column)
		{
			TSharedPtr<FMILineBorder> BorderPtr = MakeShared<FMILineBorder>(Column + 1, Row, Column + 1, Row + 1);
			AdjacencyList[GetVertexIndex(Row, Column)].Add(FMIEdge(GetVertexIndex(Row, Column + 1), BorderPtr));
			AdjacencyList[GetVertexIndex(Row, Column + 1)].Add(FMIEdge(GetVertexIndex(Row, Column), BorderPtr));
		}
	}


	for (int32 Row = 0; Row < Height - 1; ++Row)
	{
		for (int32 Column = 0; Column < Width; ++Column)
		{
			TSharedPtr<FMILineBorder> BorderPtr = MakeShared<FMILineBorder>(Column, Row + 1, Column + 1, Row + 1);
			AdjacencyList[GetVertexIndex(Row, Column)].Add(FMIEdge(GetVertexIndex(Row + 1, Column), BorderPtr));
			AdjacencyList[GetVertexIndex(Row + 1, Column)].Add(FMIEdge(GetVertexIndex(Row, Column), BorderPtr));
		}
	}
}

int32 UMIRectangularMaze::GetVertices() const
{
	return Width * Height;
}

int32 UMIRectangularMaze::GetVertexIndex(const int32 Row, const int32 Column) const
{
	return Row * Width + Column;
}

TTuple<double, double, double, double> UMIRectangularMaze::GetCoordinateBounds() const
{
	return TTuple<double, double, double, double>{0, 0, Width, Height};
}
