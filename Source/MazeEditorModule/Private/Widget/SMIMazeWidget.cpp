// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SMIMazeWidget.h"
#include "SlateOptMacros.h"
#include "PropertyCustomizationHelpers.h"
#include "Subsystem/MIMazeSubsystem.h"
#include "Maze/MIMazeGenerator.h"
#include "Data/MIMazeGenerationData.h"
#include "Widget/SMI2DMazeWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SMIMazeWidget::SMIMazeWidget()
{
}


void SMIMazeWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		[
			BuildMazeDataHeader()
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		[
			BuildMazeGenerateButton()
		]

		// 아래 큰 영역
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(5)
		[
			SNew(SBorder)
			.Padding(10)
			[
				SNew(SMI2DMazeWidget)
			]
		]
	];
}

TSharedRef<SWidget> SMIMazeWidget::BuildMazeDataHeader()
{
	UMIMazeSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeSubsystem>();
	UMIMazeGenerator* MazeGenerator = Subsystem->GetMazeGenerator();

	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(5, 0)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Maze Data")))
		]

		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Center)
		.Padding(5, 0)
		[
			SNew(SObjectPropertyEntryBox)
			.AllowedClass(UMIMazeGenerationData::StaticClass())
			.AllowClear(false)
			.OnObjectChanged_Lambda([Subsystem](const FAssetData& AssetData)
			{
				UMIMazeGenerationData* Data = Cast<UMIMazeGenerationData>(AssetData.GetAsset());
				Subsystem->SetMazeGeneratorData(Data);
			})
			.ObjectPath_Lambda([Subsystem]()
			{
				if (Subsystem)
				{
					return Subsystem->GetMazeGenerationData()->GetPathName();
				}
				return FString("Maze Data");
			})
		];
}

TSharedRef<SWidget> SMIMazeWidget::BuildMazeGenerateButton()
{
	UMIMazeSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeSubsystem>();
	UMIMazeGenerator* MazeGenerator = Subsystem->GetMazeGenerator();
	
	return SNew(SButton)
		.Text(FText::FromString(TEXT("Generate Maze")))
		.OnClicked_Lambda([MazeGenerator]()
		{
			MazeGenerator->GenerateMaze();
			UE_LOG(LogTemp, Display, TEXT("Generate Maze Success!"));
			return FReply::Handled();
		});
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
