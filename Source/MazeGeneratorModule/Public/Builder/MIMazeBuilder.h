// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MICellBorder.h"
#include "MIMazeBuilder.generated.h"


/**
 * MazeBuilder
 * 미로의 노드를 바탕으로 배치되는 메쉬를 생성
 * GameVersion : 에디터에서는 사용이 불가능하다
 *
 * SimpleVersion
 */
UCLASS(Blueprintable)
class MAZEGENERATORMODULE_API UMIMazeBuilder : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeBuilder();

	void BuildMaze(const FMIGraph& InAdjacencyList, UWorld* World);

	void DestroyMaze();
	
private:
	UPROPERTY(EditAnywhere, Category = "Maze")
	TSubclassOf<AActor> LineWallActorClass;

	UPROPERTY(EditAnywhere, Category = "Maze")
	TSubclassOf<AActor> ArcWallActorClass;

	UPROPERTY()
	TArray<AActor*> BuildActors;

	UPROPERTY(EditAnywhere, Category = "Maze")
	double SizeOffset = 10.f;
};
