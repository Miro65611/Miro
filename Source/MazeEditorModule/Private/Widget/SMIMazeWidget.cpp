// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SMIMazeWidget.h"
#include "SlateOptMacros.h"
#include "Maze/MIMazeGenerator.h"
#include "Algorithm/MIMazeAlgorithm.h"
#include "MazeType/MIRectangularMaze.h"
#include "PropertyCustomizationHelpers.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SMIMazeWidget::SMIMazeWidget()
	:MazeAlgorithmClass(UMIMazeAlgorithm::StaticClass())
	,MazeType(UMIRectangularMaze::StaticClass())
{

}


void SMIMazeWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(2.0f, 2.0f) 
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(0.f, 0.f, 4.f, 0.f) // 오른쪽에만 약간의 여백
						[
							SNew(STextBlock)
								.Text(FText::FromString("Maze Algorithm:"))
						]

						+ SHorizontalBox::Slot()
						.VAlign(VAlign_Center)
						[
							SNew(SClassPropertyEntryBox)
								.MetaClass(UMIMazeAlgorithm::StaticClass())
								.SelectedClass(this, &SMIMazeWidget::GetMazeAlorithmClass)
								.OnSetClass(this, &SMIMazeWidget::OnMazeAlgorithmClassChanged)
								.AllowNone(false)
						]
				]
		];
}

FString SMIMazeWidget::GetMazeAlgorithmPath() const
{
	return MazeAlgorithmClass ? MazeAlgorithmClass->GetPathName() : FString();
}

void SMIMazeWidget::OnMazeAlgorithmClassChanged(const UClass* InClass)
{
	MazeAlgorithmClass = const_cast<UClass*>(InClass);

	MazeGenerator = MakeShared<UMIMazeGenerator>();

}

int32 SMIMazeWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 MazeWidth = 20;
	int32 MazeHeight = 20;
	int32 CellSize = 20.f;

	for (int32 Y = 0; Y < MazeHeight; ++Y)
	{
		for (int32 X = 0; X < MazeWidth; ++X)
		{
			FVector2D CellPos(X * CellSize, Y * CellSize);
			//FLinearColor Color = Maze[Y][X].bWall ? FLinearColor::Black : FLinearColor::White;


			FSlateDrawElement::MakeBox(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(CellPos, FVector2D(CellSize, CellSize)),
				FCoreStyle::Get().GetBrush("WhiteBrush"),
				ESlateDrawEffect::None,
				FLinearColor::Black
			);
		}
	}
	return LayerId + 1;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
