// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SMI2DMazeWidget.h"
#include "SlateOptMacros.h"
#include "Maze/MIMaze.h"
#include "MazeType/MIRectangularMaze.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SMI2DMazeWidget::SMI2DMazeWidget()
{
	//Maze = new UMIRectangularMaze();
}

void SMI2DMazeWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/


}

int32 SMI2DMazeWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const FMIGraph& AdjacencyList = Maze->GetAdjacencyList();

	for (int32 U = 0; U < AdjacencyList.Num(); ++U)
	{
		const TArray<FMIEdge>& Edges = AdjacencyList[U];

		for (int32 V = 0; V < Edges.Num(); ++V)
		{
			TSharedPtr<FMICellBorder> CellBorder = Edges[V].Get<1>();
			TSharedPtr<FMILineBorder> LineBorder = StaticCastSharedPtr<FMILineBorder>(CellBorder);
		}

	}


	return int32();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
