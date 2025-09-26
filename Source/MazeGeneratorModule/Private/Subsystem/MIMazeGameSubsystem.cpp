// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/MIMazeGameSubsystem.h"

#include "Maze/MIMazeGenerator.h"
#include  "Builder/MIMazeBuilder.h"
#include "Data/MIMazeBuildData.h"
#include "Data/MIMazeGenerationData.h"

UMIMazeGameSubsystem::UMIMazeGameSubsystem()
{
	UE_LOG(LogTemp, Log, TEXT("GameSubsystem"));
	
	MazeGenerator = NewObject<UMIMazeGenerator>();
	MazeBuilder = NewObject<UMIMazeBuilder>();

	ConstructorHelpers::FObjectFinder<UMIMazeBuildData> BuildDataAsset(
		TEXT("/Game/MapGenerator/Data/DA_MazeBuild.DA_MazeBuild"));

	if (BuildDataAsset.Succeeded())
	{
		MazeBuildData = BuildDataAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MazeBuildData is nullptr"));
	}

	ConstructorHelpers::FObjectFinder<UMIMazeGenerationData> GenerateDataAsset(
		TEXT("/Game/MapGenerator/Data/DA_MazeGenerate.DA_MazeGenerate"));

	if (GenerateDataAsset.Succeeded())
	{
		MazeGenerateData = GenerateDataAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MazeGenerateData is nullptr"));
	}
}


void UMIMazeGameSubsystem::InitializeMaze(int32 InSeed)
{
	MazeGenerator->InitializeMaze(MazeGenerateData);
	MazeBuilder->Initialize(MazeBuildData);

	// 시드를 설정합니다
	Seed = InSeed;
	RandomStream = MakeShared<FRandomStream>(InSeed);
	MazeGenerator->SetRandomStream(RandomStream);

	// 미로의 정보를 담은 인접리스를 생성합니다.
	MazeGenerator->GenerateMaze();
	const FMIGraph& AdjacencyList = MazeGenerator->GetAdjacencyList();

	// 미로를 생성합니다
	MazeBuilder->BuildMaze(AdjacencyList ,GetWorld());
}

