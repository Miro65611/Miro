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

	void Temp();
	
protected:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override; 

private:
	// 미로 데이터를 저장할 배열 (0: 벽, 1: 길)
	TArray<TArray<int32>> MazeData;
};
