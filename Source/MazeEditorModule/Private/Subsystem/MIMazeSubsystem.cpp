// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/MIMazeSubsystem.h"

#include "Maze/MIMazeGenerator.h"
#include "Data/MIMazeGenerationData.h"

UMIMazeSubsystem::UMIMazeSubsystem()
{
	MazeGenerator = NewObject<UMIMazeGenerator>();
}

void UMIMazeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("UMIMazeSubsystem::Initialize"));
}

void UMIMazeSubsystem::Deinitialize()
{
}

UMIMazeGenerator* UMIMazeSubsystem::GetMazeGenerator()
{
	return MazeGenerator;
}

UMIMazeGenerationData* UMIMazeSubsystem::GetMazeGenerationData()
{
	return MazeGenerationData;
}

void UMIMazeSubsystem::SetMazeGeneratorData(UMIMazeGenerationData* Data)
{
	MazeGenerationData = Data;
	
	// MazeGenerator 설정
	MazeGenerator->InitializeMaze(Data);
	SetRandomStream(0);
}

void UMIMazeSubsystem::SetRandomStream(int32 InSeed)
{
	Seed = InSeed;
	RandomStream = MakeShared<FRandomStream>(InSeed);
	MazeGenerator->SetRandomStream(RandomStream);
}
