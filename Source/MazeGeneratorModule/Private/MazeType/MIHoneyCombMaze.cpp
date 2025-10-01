// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeType/MIHoneyCombMaze.h"


const int UMIHoneyCombMaze::NeighborDeltas[6][2] = {
	{-1, 0}, {-1, 1}, {0, 1},
	{1, 0}, {1, -1}, {0, -1}
};

UMIHoneyCombMaze::UMIHoneyCombMaze()
{
}

void UMIHoneyCombMaze::InitializeGraph(FMIGraph& InAdjacencyList)
{
	Super::InitializeGraph(InAdjacencyList);

	InAdjacencyList.SetNum(GetVertices());
	
	for (int32 U = -Size + 1; U < Size; ++U)
	{
		const TPair<int32, int32> Range = GetVCoordinateRange(U);
		for (int32 V = Range.Get<0>(); V <= Range.Get<1>(); ++V)
		{
			int32 Node = GetVertexIndex(U, V);
			for (int32 N = 0; N < 6; ++N)
			{
				const int32 UU = U + NeighborDeltas[N][0];
				const int32 VV = V + NeighborDeltas[N][1];
				if (IsValidNode(UU, VV))
				{
					int32 NeighborNode = GetVertexIndex(UU, VV);
					if (NeighborNode > Node) continue;
					TSharedPtr<FMILineBorder> Ptr = MakeShared<FMILineBorder>(GetEdge(U, V, N));

					InAdjacencyList[Node].Add({NeighborNode, Ptr});
					InAdjacencyList[NeighborNode].Add({Node, Ptr});
				}
				else
				{
					InAdjacencyList[Node].Add({-1, MakeShared<FMILineBorder>(GetEdge(U, V, N))});
				}
			}
		}
	}
}

TTuple<double, double, double, double> UMIHoneyCombMaze::GetCoordinateBounds() const
{
	double XLim = FMath::Sqrt(3.) * (Size - 0.5);
	double YLim = 1.5 * Size - 0.5;
	return {-XLim, -YLim, XLim, YLim};
}

int32 UMIHoneyCombMaze::GetVertices() const
{
	return 3 * Size * (Size - 1) + 1;
}

int32 UMIHoneyCombMaze::GetVertexIndex(int32 U, int32 V) const
{
	if (U <= 0)
	{
		return ((3 * Size + U) * (Size + U - 1)) / 2 + V;
	}
	else
	{
		return (3 * Size * (Size - 1) + (4 * Size - U - 1) * U)  / 2 + V;
	}
}

bool UMIHoneyCombMaze::IsValidNode(int32 U, int32 V) const
{
	if (U <= -Size || U >= Size)
	{
		return false;
	}

	const TPair<int32, int32> Range = GetVCoordinateRange(U);
	return V >= Range.Get<0>() && V <= Range.Get<1>();
}

TPair<int32, int32> UMIHoneyCombMaze::GetVCoordinateRange(int32 U) const
{
	if (U < 0)
	{
		return {-Size - U + 1, Size - 1};
	}

	return {-Size + 1, Size - 1 - U};
}

TTuple<double, double, double, double> UMIHoneyCombMaze::GetEdge(int32 U, int32 V, int32 Edge) const
{
	const double Udx = FMath::Sqrt(3.) / 2;
	constexpr double Udy = 1.5;
	const double Vdx = FMath::Sqrt(3.);
	constexpr double Vdy = 0;

	const double Cx = Udx * U + Vdx * V;
	const double Cy = Udy * U + Vdy * V;

	const double Theta1 = (Edge - 2.5) * PI / 3.;
	const double Theta2 = Theta1 + PI / 3.;

	return MakeTuple(Cx + FMath::Cos(Theta1), Cy + FMath::Sin(Theta1), Cx + FMath::Cos(Theta2),
	                 Cy + FMath::Sin(Theta2));
}
