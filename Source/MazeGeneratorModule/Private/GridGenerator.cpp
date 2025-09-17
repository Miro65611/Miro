// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerator.h"

UGridGenerator::UGridGenerator()
	:Seed(0)
	,RandomStream(0)
{}

UGridGenerator::UGridGenerator(FSeed InSeed)
	:Seed(InSeed)
	,RandomStream(InSeed.SeedNumber)
{}

FGrid UGridGenerator::GernerateGridData(uint32 Width, uint32 Height) const
{
	FGrid NewGrid(Width, Height);
	
	return NewGrid;
}


