// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MILineBorder.generated.h"

UCLASS()
class MAZEGENERATORMODULE_API AMILineBorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMILineBorder();

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LineMeshComponent;
};
