// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FMICellBorder
{
public:
};


/// <summary>
/// 직선 형태 벽
/// (X1,Y1)----(X2,Y2) 직선
/// </summary>
class FMILineBorder : public FMICellBorder
{
public:
	FMILineBorder();
	FMILineBorder(double InX1, double InY1, double InX2, double InY2);

protected:
	double X1;
	double Y1;
	double X2;
	double Y2;
};

/// <summary>
/// 호 형태 벽
/// 
///		   < (Theta2)
///	      <	 
///    R <
///	    <
///	   <
///   < < < < < <(Theta1)
/// (X,Y)
/// 대충 이런느낌 
/// </summary>
class FMIArcBorder : public FMICellBorder
{
public:
	FMIArcBorder();
	FMIArcBorder(double CenterX, double CenterY, double Radius, double Theta1, double Theta2);

protected:
	double CenterX;
	double CenterY;
	double Radius;
	double Theta1;
	double Theta2;
};

using FMIEdge = TTuple<int32, TSharedPtr<FMICellBorder>>;
using FMIGraph = TArray<TArray<FMIEdge>>;
using FMISpanningTree = TArray<TPair<int32, int32>>;