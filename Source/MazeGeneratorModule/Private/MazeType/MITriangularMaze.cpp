// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeType/MITriangularMaze.h"
#include "Maze/MICellBorder.h"


UMITriangularMaze::UMITriangularMaze()
{
}

void UMITriangularMaze::InitializeGraph(FMIGraph& InAdjacencyList)
{
	Super::InitializeGraph(InAdjacencyList);
	StartVertex = 0;
	EndVertex = GetVertices() - 1;
	InAdjacencyList.SetNum(GetVertices());

	// Top boundary
	for (int32 Index = 0; Index < GetCellsInRow(0); ++Index)
	{
		InAdjacencyList[GetVertexIndex(0, Index)].Add(
			{-1, MakeShared<FMILineBorder>(Index, 0, Index + 1, 0)});
	}

	// Bottom boundary (only 1 cell in bottom row)
	InAdjacencyList[GetVertexIndex(Rows - 1, 0)].Add(
		{-1, MakeShared<FMILineBorder>(0, Rows, 1, Rows)});

	// Left and right boundaries
	for (int32 Row = 0; Row < Rows; ++Row)
	{
		int32 CellInRow = GetCellsInRow(Row);

		// Left boundary (except for entry)
		if (Row != 0)
		{
			InAdjacencyList[GetVertexIndex(Row, 0)].Add(
				{-1, MakeShared<FMILineBorder>(0, Row, 0, Row + 1)});
		}

		// Right boundary (except for exit)
		if (!(Row == Rows - 1 && CellInRow == 1))
		{
			InAdjacencyList[GetVertexIndex(Row, CellInRow - 1)].Add(
				{-1, MakeShared<FMILineBorder>(CellInRow, Row, CellInRow, Row + 1)});
		}
	}

	// Add diagonal boundary walls on the right edge
	for (int Row = 0; Row < Rows - 1; ++Row)
	{
		int CellsInRow = GetCellsInRow(Row);
		int CellsInNextRow = GetCellsInRow(Row + 1);

		// Add diagonal wall from rightmost cell of current row to rightmost cell of next row
		if (!(Row == Rows - 2 && CellsInNextRow == 1))
		{
			// except for exit
			InAdjacencyList[GetVertexIndex(Row, CellsInRow - 1)].Add(
				{-1, MakeShared<FMILineBorder>(CellsInRow, Row + 1, CellsInNextRow, Row + 1)});
		}
	}

	// Horizontal connections within each row
	for (int Row = 0; Row < Rows; ++Row)
	{
		const int32 CellInRow = GetCellsInRow(Row);
		for (int Col = 0; Col < CellInRow - 1; ++Col)
		{
			TSharedPtr<FMILineBorder> Ptr =
				MakeShared<FMILineBorder>(Col + 1, Row, Col + 1, Row + 1);
			InAdjacencyList[GetVertexIndex(Row, Col)].Add({GetVertexIndex(Row, Col + 1), Ptr});
			InAdjacencyList[GetVertexIndex(Row, Col + 1)].Add({GetVertexIndex(Row, Col), Ptr});
		}
	}

	// Vertical connections between rows
	for (int Row = 0; Row < Rows - 1; ++Row)
	{
		int32 CellsInNextRow = GetCellsInRow(Row + 1);
		for (int32 Col = 0; Col < CellsInNextRow; ++Col)
		{
			TSharedPtr<FMILineBorder> Ptr =
				MakeShared<FMILineBorder>(Col, Row + 1, Col + 1, Row + 1);
			InAdjacencyList[GetVertexIndex(Row, Col)].Add({GetVertexIndex(Row + 1, Col), Ptr});
			InAdjacencyList[GetVertexIndex(Row + 1, Col)].Add({GetVertexIndex(Row, Col), Ptr});
		}
	}
}

TTuple<double, double, double, double> UMITriangularMaze::GetCoordinateBounds() const
{
	return MakeTuple(0, 0, Rows, Rows);
}

int32 UMITriangularMaze::GetVertices() const
{
	return Rows * (Rows + 1) / 2;
}

int32 UMITriangularMaze::GetVertexIndex(const int32 Row, const int32 Col) const
{
	return GetCellsBeforeRow(Row) + Col;
}

int32 UMITriangularMaze::GetCellsInRow(const int32 Row) const
{
	return Rows - Row;
}

int32 UMITriangularMaze::GetCellsBeforeRow(const int Row) const
{
	int32 Total = 0;
	for (int R = 0; R < Row; R++)
	{
		Total += GetCellsInRow(R);
	}

	return Total;
}
