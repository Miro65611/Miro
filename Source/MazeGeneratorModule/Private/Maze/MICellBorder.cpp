// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/MICellBorder.h"


FMILineBorder::FMILineBorder()
	:X1{}, Y1{}, X2{}, Y2{}
{
}

FMILineBorder::FMILineBorder(double InX1, double InY1, double InX2, double InY2)
	:X1(InX1), Y1(InY1), X2(InX2), Y2(InY2)
{
}

ECellBorderType FMILineBorder::GetCellBorderType() const
{
	return ECellBorderType::Line;
}

FMIArcBorder::FMIArcBorder()
	:CenterX(0), CenterY(0), Radius(0), Theta1(0), Theta2(0)
{
}

FMIArcBorder::FMIArcBorder(double CenterX, double CenterY, double Radius, double Theta1, double Theta2)
	:CenterX(CenterX), CenterY(CenterY), Radius(Radius), Theta1(Theta1), Theta2(Theta2)
{
}

ECellBorderType FMIArcBorder::GetCellBorderType() const
{
	return ECellBorderType::Arc;
}
	