// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ECellBorderType
{
	Line,
	Arc,
	None,
};

class FMICellBorder
{
public:
	virtual ~FMICellBorder(){}

	virtual ECellBorderType GetCellBorderType() const abstract;
};

// 직선 벽
class FMILineBorder : public FMICellBorder
{
public:
	FMILineBorder();
	FMILineBorder(double InX1, double InY1, double InX2, double InY2);
	FMILineBorder(TTuple<double, double,double,double>);
	
	double X1;
	double Y1;
	double X2;
	double Y2;

public:
	virtual ECellBorderType GetCellBorderType() const override;
};

// 호 모양 벽
class FMIArcBorder : public FMICellBorder
{
public:
	FMIArcBorder();
	FMIArcBorder(double CenterX, double CenterY, double Radius, double Theta1, double Theta2);

	double CenterX;
	double CenterY;
	double Radius;
	double Theta1;
	double Theta2;

	virtual ECellBorderType GetCellBorderType() const override;
};

using FMIEdge = TTuple<int32, TSharedPtr<FMICellBorder>>;
using FMIGraph = TArray<TArray<FMIEdge>>;
using FMISpanningTree = TArray<TPair<int32, int32>>;
