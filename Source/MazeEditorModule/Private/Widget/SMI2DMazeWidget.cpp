// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SMI2DMazeWidget.h"
#include "SlateOptMacros.h"
#include "Maze/MIMazeGenerator.h"
#include "MazeType/MIMazeType.h"
#include "MazeType/MIRectangularMaze.h"
#include "Subsystem/MIMazeEditorSubsystem.h"

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

	UMIMazeEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeEditorSubsystem>();

	const FMIGraph& AdjacencyList = Subsystem->GetMazeGenerator()->GetAdjacencyList();

	// Clipping 
	const FSlateClippingZone ClippingZone(AllottedGeometry.GetLayoutBoundingRect());
	OutDrawElements.PushClip(ClippingZone);

	// 선분을 그릴 점들을 정의합니다.
	for (int32 Index1 = 0; Index1 < AdjacencyList.Num(); ++Index1)
	{
		const TArray<FMIEdge>& Edges = AdjacencyList[Index1];

		for (int32 V = 0; V < Edges.Num(); ++V)
		{
			constexpr float ScaleStep = 10.f;
			constexpr float Thickness = 0.5f;

			const TSharedPtr<FMICellBorder>& CellBorder = Edges[V].Get<1>();
			const FLinearColor LineColor = FLinearColor::White;


			// dynamic cast  사용하기에는 좀..... 그렇다고 UObject로 만들기에도 좀.....
			if (CellBorder->GetCellBorderType() == ECellBorderType::Line)
			{
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
			else if (CellBorder->GetCellBorderType() == ECellBorderType::Arc)
			{
				// 아치모양 그리기 함수 지원해줘 빽!
				const TSharedPtr<FMIArcBorder>& ArcBorder = StaticCastSharedPtr<FMIArcBorder>(CellBorder);

				double CenterX = ArcBorder->CenterX;
				double CenterY = ArcBorder->CenterY;
				double Radius = ArcBorder->Radius;
				double Theta1 = ArcBorder->Theta1;
				double Theta2 = ArcBorder->Theta2;

				constexpr int32 NumSegments = 64;

				TArray<FVector2D> ArcPoints;
				ArcPoints.Reserve(NumSegments + 1);

				for (int32 Index = 0; Index < NumSegments; ++Index)
				{
					double Alpha = FMath::Lerp(Theta1, Theta2,
					                           static_cast<double>(Index) / static_cast<double>(NumSegments));
					double X = CenterX + Radius * FMath::Cos(Alpha);
					double Y = CenterY + Radius * FMath::Sin(Alpha);
					ArcPoints.Add(FVector2D(X * ScaleStep, Y * ScaleStep));
				}

				FSlateDrawElement::MakeLines(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(), // 로컬 좌표 → 페인트 좌표 변환
					ArcPoints,
					DrawEffects,
					LineColor,
					true, // Anti-Aliasing 여부
					Thickness
				);
			}
			else if (CellBorder->GetCellBorderType() == ECellBorderType::None)
			{
			}
		}
	}

	OutDrawElements.PopClip();

	return LayerId + 1;
}

FReply SMI2DMazeWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		const FVector2D CursorDelta = MouseEvent.GetCursorDelta();

		const TScale2<float>& CurrentScale = GetRenderTransform()->GetMatrix().GetScale();
		const FVector2D CurrentTranslation = GetRenderTransform()->GetTranslation();;

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
