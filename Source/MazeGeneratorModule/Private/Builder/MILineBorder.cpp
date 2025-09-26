// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder/MILineBorder.h"

AMILineBorder::AMILineBorder()
{
	PrimaryActorTick.bCanEverTick = true;

	LineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LineMesh"));
	RootComponent = LineMeshComponent;
}

