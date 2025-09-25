// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
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

private:
	TSharedRef<SWidget> BuildMazeDataHeader();
	TSharedRef<SWidget> BuildMazeGenerateButton();
	TSharedRef<SWidget> BuildMazeBuildButton();
	TSharedRef<SWidget> BuildSeedInputButton();
	
};
