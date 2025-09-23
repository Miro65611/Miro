// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Maze/MICellBorder.h"
#include "MIMazeGenerator.generated.h"

class UMIMazeType;
class UMIMazeAlgorithm;
class UMIMazeGenerationData;

/**
 * 미로 생성 클래스
 */
UCLASS()
class MAZEGENERATORMODULE_API UMIMazeGenerator : public UObject
{
	GENERATED_BODY()

public:
	UMIMazeGenerator();
	UMIMazeGenerator(UMIMazeType* MazeType, UMIMazeAlgorithm* MazeAlgorithm);

	// 미로를 생성을 위한 랜덤 스트림(시드)를 설정합니다
	void SetRandomStream(const TSharedPtr<FRandomStream>& InRandomStream);

	// 미로를 초기화합니다
	void InitializeMaze(const UMIMazeGenerationData* MazeGenerationData);

	// 알고리즘과 미로형태를 바탕으로 새로운 미모를 생성합니다
	void GenerateMaze();
	
	const FMIGraph& GetAdjacencyList()const {return AdjacencyList;};
	
private:
	
	void RemoveBorders(const TArray<TPair<int32, int32>>& Edges);
	
private:
	UPROPERTY()
	TObjectPtr<UMIMazeType> MazeType;

	UPROPERTY()
	TObjectPtr<UMIMazeAlgorithm> MazeAlgorithm;

	int32 StartVertex;
	int32 EndVertex;
	FMIGraph AdjacencyList;
	FMIGraph Solution;
	int32 Vertices; 

	TSharedPtr<FRandomStream> RandomStream;
};
