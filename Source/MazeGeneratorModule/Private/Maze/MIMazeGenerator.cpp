// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/MIMazeGenerator.h"
#include "Maze/MIMaze.h"
#include "Algorithm/MIMazeAlgorithm.h"

UMIMazeGenerator::UMIMazeGenerator()
	:Maze(nullptr)
	,MazeAlgorithm(nullptr)
{}

void UMIMazeGenerator::GenerateMaze()
{
	Maze->InitializeGraph();
	Maze->GenerateMaze(MazeAlgorithm.Get());

}
