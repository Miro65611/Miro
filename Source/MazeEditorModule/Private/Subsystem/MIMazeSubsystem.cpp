// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/MIMazeSubsystem.h"

#include "Maze/MIMazeGenerator.h"
#include "Data/MIMazeGenerationData.h"
#include "Builder/MIMazeBuilder.h"


UMIMazeSubsystem::UMIMazeSubsystem()
{
	MazeGenerator = NewObject<UMIMazeGenerator>();

	ConstructorHelpers::FClassFinder<UObject> MazeBuilderBPClass(
		TEXT("/Game/MapGenerator/Blueprint/BP_MazeBuilder.BP_MazeBuilder_C"));
	if (MazeBuilderBPClass.Succeeded())
	{
		MazeBuilderClass = MazeBuilderBPClass.Class;
	}
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

void UMIMazeSubsystem::BuildMaze()
{
	if (MazeBuilder == nullptr)
	{
		MazeBuilder = NewObject<UMIMazeBuilder>(this, MazeBuilderClass);
	}

	UWorld* World = nullptr;
	if (GEditor->PlayWorld) // PIE 실행 중
	{
		World = GEditor->PlayWorld;
	}
	else
	{
		World = GEditor->GetEditorWorldContext().World();
	}
	
	MazeBuilder->BuildMaze(MazeGenerator->GetAdjacencyList(), World);
}

void UMIMazeSubsystem::DestroyMaze()
{
	if (MazeBuilder == nullptr)
	{
		MazeBuilder = NewObject<UMIMazeBuilder>(this, MazeBuilderClass);
	}
	
	MazeBuilder->DestroyMaze();
}


void UMIMazeSubsystem::SetRandomStream(int32 InSeed)
{
	Seed = InSeed;
	RandomStream = MakeShared<FRandomStream>(InSeed);
	MazeGenerator->SetRandomStream(RandomStream);
}
