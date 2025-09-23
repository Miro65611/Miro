// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 2D 
 */
class MAZEEDITORMODULE_API SMI2DMazeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMI2DMazeWidget)
	{}
	SLATE_END_ARGS()


	SMI2DMazeWidget();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


protected:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
		int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
	class UMIMaze* Maze;
};
