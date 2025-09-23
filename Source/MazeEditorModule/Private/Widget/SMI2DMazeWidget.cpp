// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SMI2DMazeWidget.h"
#include "SlateOptMacros.h"
#include "Maze/MIMazeGenerator.h"
#include "MazeType/MIMazeType.h"
#include "MazeType/MIRectangularMaze.h"
#include "Subsystem/MIMazeSubsystem.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SMI2DMazeWidget::Construct(const FArguments& InArgs)
{
	// 미로 데이터 초기화 (예제)
	MazeData = {
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 0, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0}
	};

	// ChildSlot
	// [
	// 	// 아무 자식 위젯도 추가하지 않으므로 비워둡니다.
	// 	// OnPaint() 함수에서 직접 그리기 때문에 컨테이너만 제공
	//
	// ];
}

void SMI2DMazeWidget::Temp()
{
	UMIMazeSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeSubsystem>();
	if (Subsystem)
	{
		Subsystem->GetMazeGenerator();
	}
}


int32 SMI2DMazeWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                               const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                               const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);
	const ESlateDrawEffect DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	UMIMazeSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeSubsystem>();
	const FMIGraph& AdjacencyList = Subsystem->GetMazeGenerator()->GetAdjacencyList();


	// 선분의 색상과 두께를 정의합니다.
	const FLinearColor LineColor = FLinearColor::Red;

	// 선분을 그릴 점들을 정의합니다.
	for (int32 Index1 = 0; Index1 < AdjacencyList.Num(); ++Index1)
	{
		const TArray<FMIEdge>& Edges = AdjacencyList[Index1];

		for (int32 V = 0; V < Edges.Num(); ++V)
		{
			const int32 Index2 = Edges[V].Get<0>();
			const TSharedPtr<FMICellBorder>& CellBorder = Edges[V].Get<1>();
			const TSharedPtr<FMILineBorder>& LineBorder = StaticCastSharedPtr<FMILineBorder>(CellBorder);

			TArray<FVector2D> Points;
			Points.Add({LineBorder->X1 * 20.f, LineBorder->Y1 * 20.f});
			Points.Add({LineBorder->X2 * 20.f, LineBorder->Y2 * 20.f});

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(), // 로컬 좌표 → 페인트 좌표 변환
				Points,
				DrawEffects,
				LineColor,
				true, // Anti-Aliasing 여부
				0.5f
			);
		}
	}

	// MakeLines 함수를 사용하여 선을 그립니다.
	return LayerId;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
