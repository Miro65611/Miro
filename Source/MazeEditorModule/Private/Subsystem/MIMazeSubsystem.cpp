// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/MIMazeSubsystem.h"

#include "Chaos/Deformable/MuscleActivationConstraints.h"
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
}

bool UMIMazeSubsystem::InitializeMaze()
{
	if (!IsValid(MazeGenerationData))
	{
		UE_LOG(LogTemp, Error, TEXT("MazGeneration is not Set"));
		return false;
	}
	
	MazeGenerator->InitializeMaze(MazeGenerationData);
	SetRandomStream(Seed);

	return true;
}

void UMIMazeSubsystem::GenerateMaze() 
{
	MazeGenerator->GenerateMaze();
}


void UMIMazeSubsystem::SetRandomStream(int32 InSeed)
{
	Seed = InSeed;
	RandomStream = MakeShared<FRandomStream>(InSeed);
	MazeGenerator->SetRandomStream(RandomStream);
}
