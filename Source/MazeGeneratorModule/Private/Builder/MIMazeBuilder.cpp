// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder/MIMazeBuilder.h"


UMIMazeBuilder::UMIMazeBuilder()
{
}

void UMIMazeBuilder::BuildMaze(const FMIGraph& InAdjacencyList, UWorld* World)
{
	for (int32 EdgeIndex = 0; EdgeIndex < InAdjacencyList.Num(); EdgeIndex++)
	{
		for (const auto& [OtherEdgeIndex , CellBorder] : InAdjacencyList[EdgeIndex])
		{
			const ECellBorderType CellBorderType = CellBorder->GetCellBorderType();

			if (CellBorderType == ECellBorderType::Line)
			{
				// Line 벽생성
				const TSharedPtr<FMILineBorder>& LineBorder = StaticCastSharedPtr<FMILineBorder>(CellBorder);

				FVector Location = {LineBorder->X1, LineBorder->Y1, 0};

				FVector Start(LineBorder->X1, LineBorder->Y1, 0.f);
				FVector End(LineBorder->X2, LineBorder->Y2, 0.f);

				FVector Direction = (End - Start).GetSafeNormal();
				FRotator LookRotation = Direction.Rotation();
				
				Location*= SizeOffset;

				AActor* BuildActor = World->SpawnActor(LineWallActorClass, &Location,&LookRotation);
				BuildActors.Add(BuildActor);
			}
			else if (CellBorderType == ECellBorderType::Arc)
			{
				// Arc 벽 생성
			}
		}
	}
}

void UMIMazeBuilder::DestroyMaze()
{
	for (AActor* BuildActor : BuildActors)
	{
		if (BuildActor && !BuildActor->IsPendingKillPending())
		{
			BuildActor->Destroy();
		}
	}
	BuildActors.Empty();
}
