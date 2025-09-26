// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SMIMazeWidget.h"
#include "SlateOptMacros.h"
#include "PropertyCustomizationHelpers.h"
#include "Subsystem/MIMazeEditorSubsystem.h"
#include "Data/MIMazeGenerationData.h"
#include "Widget/SMI2DMazeWidget.h"
#include "Widgets/Input/SNumericEntryBox.h"

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
			BuildSeedInputButton()
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		[
			BuildMazeBuildButton()
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(5)
		[
			BuildMazeGenerateButton()
		]

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
	UMIMazeEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeEditorSubsystem>();

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
	UMIMazeEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeEditorSubsystem>();

	return SNew(SButton)
		.Text(FText::FromString(TEXT("Generate Maze")))
		.OnClicked_Lambda([Subsystem]()
		{
			if (bool bSuccessInit = Subsystem->InitializeMaze())
			{
				Subsystem->GenerateMaze();
				UE_LOG(LogTemp, Display, TEXT("Generate Maze Success!"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Generate Maze Fail!"));
			}


			return FReply::Handled();
		});
}

TSharedRef<SWidget> SMIMazeWidget::BuildMazeBuildButton()
{
	UMIMazeEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeEditorSubsystem>();

	return SNew(SButton)
		.Text(FText::FromString(TEXT("Build Maze")))
		.OnClicked_Lambda([Subsystem]()
		{
			Subsystem->DestroyMaze();
			Subsystem->BuildMaze();

			return FReply::Handled();
		});
}

TSharedRef<SWidget> SMIMazeWidget::BuildSeedInputButton()
{
	return SNew(SNumericEntryBox<int32>)
		.MinValue(MIN_int32)
		.MaxValue(MAX_int32)
		.Value(0)
		.OnValueCommitted_Lambda([this](const int32 Seed, const ETextCommit::Type CommitType)
		{
			if (CommitType == ETextCommit::Type::OnEnter)
			{
				UMIMazeEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMIMazeEditorSubsystem>();
				Subsystem->SetRandomStream(Seed);
			}

			UE_LOG(LogTemp, Log, TEXT("Seed Committed: %d"), Seed);
			//SeedValue = NewValue;
		});
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
