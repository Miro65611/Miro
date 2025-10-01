// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder/MIMazeBuilder.h"

#include "Builder/MIArcBorder.h"
#include "Builder/MILineBorder.h"
#include "Data/MIMazeBuildData.h"

UMIMazeBuilder::UMIMazeBuilder()
{
}

void UMIMazeBuilder::BuildMaze(const FMIGraph& InAdjacencyList, UWorld* World)
{
	ensure(RootMaze == nullptr);

	BuildRootMaze(World);

	for (int32 EdgeIndex = 0; EdgeIndex < InAdjacencyList.Num(); EdgeIndex++)
	{
		for (const auto& [OtherEdgeIndex , CellBorder] : InAdjacencyList[EdgeIndex])
		{
			const ECellBorderType CellBorderType = CellBorder->GetCellBorderType();

			if (CellBorderType == ECellBorderType::Line)
			{
				const FMILineBorder* LineBorder = StaticCast<FMILineBorder*>(CellBorder.Get());
				BuildLineBorder(LineBorder, World);
			}
			else if (CellBorderType == ECellBorderType::Arc)
			{
				const FMIArcBorder* ArcBorder = StaticCast<FMIArcBorder*>(CellBorder.Get());
				BuildArcBorder(ArcBorder, World);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Unsupported cell border type!")); 
			}
		}
	}
}

void UMIMazeBuilder::DestroyMaze()
{
	if (IsValid(RootMaze))
	{
		RootMaze->Destroy();
		RootMaze = nullptr;
	}
}

void UMIMazeBuilder::Initialize(const UMIMazeBuildData* MazeBuildData)
{
	ArcBorderClass = MazeBuildData->ArcBorderClass;
	LineBorderClass = MazeBuildData->LineBorderClass;

	MazeWorldOffset = MazeBuildData->MazeWorldOffset;
	MazeToWorldScale = MazeBuildData->MazeToWorldScale;
}

void UMIMazeBuilder::BuildRootMaze(UWorld* World)
{
	const FTransform SpawnTransform{FRotator::ZeroRotator, MazeWorldOffset};

	RootMaze = World->SpawnActor(AActor::StaticClass(), &SpawnTransform);

	if (RootMaze)
	{
		USceneComponent* SceneComponent = NewObject<USceneComponent>(RootMaze, TEXT("RootMaze"));
		SceneComponent->RegisterComponent();
		RootMaze->SetRootComponent(SceneComponent);
	}
}

void UMIMazeBuilder::BuildLineBorder(const FMILineBorder* LineBorder, UWorld* World)
{
	FVector Location = {LineBorder->X1, LineBorder->Y1, 0};

	const FVector Start(LineBorder->X1, LineBorder->Y1, 0.f);
	const FVector End(LineBorder->X2, LineBorder->Y2, 0.f);

	const FVector Direction = (End - Start).GetSafeNormal();
	const FRotator LookRotation = Direction.Rotation();

	Location *= MazeToWorldScale;

	AActor* LineBorderActor = World->SpawnActor(LineBorderClass, &Location, &LookRotation);

	LineBorderActor->AttachToActor(RootMaze, FAttachmentTransformRules::KeepWorldTransform);
}

void UMIMazeBuilder::BuildArcBorder(const FMIArcBorder* ArcBorder, UWorld* World)
{
	const double CenterX = ArcBorder->CenterX;
	const double CenterY = ArcBorder->CenterY;

	const double Theta1 = ArcBorder->Theta1;
	const double Theta2 = ArcBorder->Theta2;

	const double Angle = Theta2 - Theta1;

	const FRotator Rotation{0.f, FMath::RadiansToDegrees(Theta1), 0.f};
	FVector Location = FVector(CenterX, CenterY, 0);

	Location *= MazeToWorldScale;

	AActor* Actor = World->SpawnActor(ArcBorderClass, &Location  , &Rotation);

	if (AMIArcBorder* ArcBorderActor = Cast<AMIArcBorder>(Actor); ArcBorder)
	{
		const double Radius = ArcBorder->Radius * MazeToWorldScale;
		const int32 Segments = FMath::Max(static_cast<int32>(FMath::RadiansToDegrees(Angle) / 30.),2 );

		ArcBorderActor->SetBuildData(Radius, Angle, Segments);
		ArcBorderActor->Build();
		
		Actor->AttachToActor(RootMaze, FAttachmentTransformRules::KeepWorldTransform);
	}
}
