// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 2DMaze  
 */
class MAZEEDITORMODULE_API SMI2DMazeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMI2DMazeWidget)
	{}
	SLATE_END_ARGS()

	/** 위젯 생성 및 초기화 */
	void Construct(const FArguments& InArgs);

protected:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override; 

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
	
};
