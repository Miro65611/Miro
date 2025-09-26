// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MICellBorder.h"
#include "MIMazeBuilder.generated.h"

class AMILineBorder;
class AMIArcBorder;

class UMIMazeBuildData;

/**
 * MazeBuilder
 * 미로의 노드를 바탕으로 배치되는 메쉬를 생성
 *
 * SimpleVersion
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeBuilder : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeBuilder();

	// 미로를 빌드합니다
	void BuildMaze(const FMIGraph& InAdjacencyList, UWorld* World);

	// 월드에 생성했던 미로를 제거합니다
	void DestroyMaze();

	// MazeBuilder를 초기화합니다 
	void Initialize(const UMIMazeBuildData* MazeBuildData);

protected:
	virtual void BuildRootMaze(UWorld* World);
	
	virtual void BuildLineBorder(const FMILineBorder* LineBorder, UWorld* World);

	virtual void BuildArcBorder(const FMIArcBorder* ArcBorder, UWorld* World);

private:
	UPROPERTY()
	TSubclassOf<AMIArcBorder> ArcBorderClass;

	UPROPERTY()
	TSubclassOf<AMILineBorder> LineBorderClass;
	
	UPROPERTY()
	UStaticMesh* ArcBorderMesh;
	
	FVector MazeWorldOffset;
	double MazeToWorldScale;

	UPROPERTY()
	TObjectPtr<AActor> RootMaze;
};
