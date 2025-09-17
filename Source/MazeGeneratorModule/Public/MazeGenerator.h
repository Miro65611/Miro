// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeStruct.h"
#include "MazeGenerator.generated.h"

/**
 * 전체적인 미로의 생성을 담당하는 클래스 
 */
UCLASS()
class MAZEGENERATORMODULE_API UMazeGenerator : public UObject
{
	GENERATED_BODY()
	
public:
	UMazeGenerator();

	// 1. 랜덤 시드 생성

	// 2. 그리드 생성 

	// 3. 메쉬 매치 (PCG 결합)

	// 4. 아이템 배치 

private:
	


};
