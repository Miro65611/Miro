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
	SetRenderTransform(FSlateRenderTransform(FScale2D(1.0f, 1.0f)));
}

int32 SMI2DMazeWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                               const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                               const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	++LayerId;
	
	const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);
	const ESlateDrawEffect DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	UMIMazeSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeSubsystem>();
	const FMIGraph& AdjacencyList = Subsystem->GetMazeGenerator()->GetAdjacencyList();

	// 선분의 색상과 두께를 정의합니다.
	const FLinearColor LineColor = FLinearColor::White;
	constexpr float Thickness = 0.5f;
	constexpr float ScaleStep = 10.f;

	const FSlateClippingZone ClippingZone(AllottedGeometry.GetLayoutBoundingRect());
	OutDrawElements.PushClip(ClippingZone);
	
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
			Points.Add({LineBorder->X1 * ScaleStep, LineBorder->Y1 * ScaleStep});
			Points.Add({LineBorder->X2 * ScaleStep, LineBorder->Y2 * ScaleStep});

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(), // 로컬 좌표 → 페인트 좌표 변환
				Points,
				DrawEffects,
				LineColor,
				true, // Anti-Aliasing 여부
				Thickness
			);

		}
	}

	OutDrawElements.PopClip();

	// MakeLines 함수를 사용하여 선을 그립니다.

	return LayerId +1;
}

FReply SMI2DMazeWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		const FVector2D CursorDelta = MouseEvent.GetCursorDelta();

		UE_LOG(LogTemp, Log, TEXT("CursorDelta: X=%f, Y=%f"), CursorDelta.X, CursorDelta.Y);

		const TScale2<float>& CurrentScale = GetRenderTransform()->GetMatrix().GetScale();
		const FVector2D CurrentTranslation = GetRenderTransform()->GetTranslation();;

		// 휠 입력에 따라 스케일 값 조정
		const FVector2D NewPivot = CurrentTranslation + CursorDelta;

		SetRenderTransform(FSlateRenderTransform(CurrentScale, NewPivot));
	}

	return SCompoundWidget::OnMouseMove(MyGeometry, MouseEvent);
}

FReply SMI2DMazeWidget::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const float WheelDelta = MouseEvent.GetWheelDelta();

	const TScale2<float>& CurrentScale = GetRenderTransform()->GetMatrix().GetScale();
	const FVector2D CurrentTranslation = GetRenderTransform()->GetTranslation();;

	constexpr float ScaleStep = 0.1f;
	const TScale2<float> NewScale(
		CurrentScale.GetVector().X + WheelDelta * ScaleStep,
		CurrentScale.GetVector().Y + WheelDelta * ScaleStep
	);

	SetRenderTransform(FSlateRenderTransform(NewScale, CurrentTranslation));

	return SCompoundWidget::OnMouseWheel(MyGeometry, MouseEvent);
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
