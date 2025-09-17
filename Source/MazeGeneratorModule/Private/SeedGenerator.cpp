// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedGenerator.h"
#include "Math/UnrealMathUtility.h"

USeedGenerator::USeedGenerator()
{
}

FSeed USeedGenerator::GenerateSeed()
{
	uint32 RandomInteger = FMath::RandRange(0, RAND_MAX);
	return FSeed(RandomInteger);
}

