// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MIMazeSubsystem.generated.h"

class UMIMazeGenerator;
class UMIMazeGenerationData;
class UMIMazeBuilder;

/**
 *  MazeSubsystem
 */
UCLASS()
class MAZEEDITORMODULE_API UMIMazeSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UMIMazeSubsystem();
	
	// Subsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UMIMazeGenerator* GetMazeGenerator();
	UMIMazeGenerationData* GetMazeGenerationData();

	// 미로 생성기의 데이터를 설정합니다
	void SetMazeGeneratorData(UMIMazeGenerationData* Data);

	// 미로를 초기화합니다.
	bool InitializeMaze();

	// 미로를 생성합니다
	void GenerateMaze();

	// 미로를 인스턴스화합니다
	void BuildMaze();

	// 인스턴화한 미로를 제거합니다.
	void DestroyMaze();
	
	// 랜덤 스트림을 설정합니다
	void SetRandomStream(int32 InSeed = 0);

	// 랜덤 스트림을 반환합니다
	TSharedPtr<FRandomStream> GetRandomStream()const { return RandomStream; }

	// 시드를 반환합니다
	int32 GetSeed()const {return Seed;}
	
private:
	UPROPERTY()
	TObjectPtr<UMIMazeGenerator> MazeGenerator;

	UPROPERTY()
	TObjectPtr<UMIMazeGenerationData> MazeGenerationData;

	TSubclassOf<UObject> MazeBuilderClass;
	
	UPROPERTY()
	TObjectPtr<UMIMazeBuilder> MazeBuilder;
	
	TSharedPtr<FRandomStream> RandomStream;

	int32 Seed;
};
