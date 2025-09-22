// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 미로 생성 에디터
 */
class MAZEEDITORMODULE_API SMIMazeWidget : public SCompoundWidget
{
public:
	SMIMazeWidget();

	SLATE_BEGIN_ARGS(SMIMazeWidget)
		{
		}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FString GetMazeAlgorithmPath()const;

	void OnMazeAlgorithmClassChanged(const UClass* InClass);

	const UClass* GetMazeAlorithmClass()const { return MazeAlgorithmClass; }

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
		int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


private:
	UClass* MazeAlgorithmClass = nullptr;
	UClass* MazeType = nullptr;
	TSharedPtr<class UMIMazeGenerator> MazeGenerator = nullptr;

};
