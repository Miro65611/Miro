

#pragma once

#include "CoreMinimal.h"
#include "MazeStruct.generated.h"

USTRUCT()
struct FSeed
{
	GENERATED_BODY()

	int32 SeedNumber;
};

UENUM()
enum class ECellType : uint32
{
	Wall,      // º®
	Corridor,  // º¹µµ
};

USTRUCT()
struct FCell
{
	GENERATED_BODY()

	ECellType CellType;
};

USTRUCT() 
struct FGrid
{
	GENERATED_BODY()

	FGrid()
		:Width(0), Height(0)
	{ }

	FGrid(int32 Width, int32 Height)
		:Width(Width), Height(Height)
	{
		Cells.Init(FCell(ECellType::Wall), Height * Width);
	}

	TArray<FCell> Cells;

	int32 Width;
	int32 Height;
};

