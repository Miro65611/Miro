// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/MIMazeEditorSubsystem.h"

#include "Maze/MIMazeGenerator.h"
#include "Data/MIMazeGenerationData.h"
#include "Builder/MIMazeBuilder.h"


UMIMazeEditorSubsystem::UMIMazeEditorSubsystem()
{
	MazeGenerator = NewObject<UMIMazeGenerator>();

	ConstructorHelpers::FClassFinder<UObject> MazeBuilderBPClass(
		TEXT("/Game/MapGenerator/Blueprint/BP_MazeBuilder.BP_MazeBuilder_C"));
	if (MazeBuilderBPClass.Succeeded())
	{
		MazeBuilderClass = MazeBuilderBPClass.Class;
	}
}

void UMIMazeEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("UMIMazeSubsystem::Initialize"));
}

void UMIMazeEditorSubsystem::Deinitialize()
{
}

UMIMazeGenerator* UMIMazeEditorSubsystem::GetMazeGenerator()
{
	return MazeGenerator;
}

UMIMazeGenerationData* UMIMazeEditorSubsystem::GetMazeGenerationData()
{
	return MazeGenerationData;
}

void UMIMazeEditorSubsystem::SetMazeGeneratorData(UMIMazeGenerationData* Data)
{
	MazeGenerationData = Data;
}

bool UMIMazeEditorSubsystem::InitializeMaze()
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

void UMIMazeEditorSubsystem::GenerateMaze()
{
	MazeGenerator->GenerateMaze();
}

void UMIMazeEditorSubsystem::BuildMaze()
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
	
	MazeBuilder->BuildMaze(MazeGenerator->GetAdjacencyList(),GetWorld());
}

void UMIMazeEditorSubsystem::DestroyMaze()
{
	if (MazeBuilder == nullptr)
	{
		MazeBuilder = NewObject<UMIMazeBuilder>(this, MazeBuilderClass);
	}
	
	MazeBuilder->DestroyMaze();
}


void UMIMazeEditorSubsystem::SetRandomStream(int32 InSeed)
{
	Seed = InSeed;
	RandomStream = MakeShared<FRandomStream>(InSeed);
	MazeGenerator->SetRandomStream(RandomStream);
}
