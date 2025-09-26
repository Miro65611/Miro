// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder/MIArcBorder.h"

#include "SkeletonTreeBuilder.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AMIArcBorder::AMIArcBorder()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(SplineComponent);
}

void AMIArcBorder::Build()
{
	BuildSpline();
	BuildArcMesh();
}

void AMIArcBorder::SetBuildData(double InRadius, double InAngleRadian, int32 InSegments)
{
	Radius= InRadius;
	AngleRadian= InAngleRadian;
	Segments = InSegments;
}

void AMIArcBorder::BuildSpline()
{
	if (!SplineComponent || Segments <= 0) return;

	SplineComponent->ClearSplinePoints();

	if (AngleRadian >= UE_DOUBLE_TWO_PI)
	{
		AngleRadian = UE_DOUBLE_TWO_PI;
		SplineComponent->SetClosedLoop(true);
	}
	else
	{
		SplineComponent->SetClosedLoop(false);
	}

	const double AngleStep = AngleRadian / static_cast<double>(Segments);

	for (int32 Index = 0; Index <= Segments; Index++)
	{
		const float Angle = Index * AngleStep;

		FVector Position = FVector(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 0.0f);

		SplineComponent->AddSplineLocalPoint(Position);
	}

	SplineComponent->UpdateSpline();
}

void AMIArcBorder::BuildArcMesh()
{
	for (USplineMeshComponent* SplineMesh : SplineMeshes)
	{
		if (SplineMesh)
		{
			SplineMesh->DestroyComponent();
		}
	}

	SplineMeshes.Empty();

	if (!ArcMesh || SplineComponent->GetNumberOfSplinePoints() <= 1) return;

	const int32 NumSegments = SplineComponent->GetNumberOfSplinePoints() - 1;

	for (int32 i = 0; i < NumSegments; i++)
	{
		USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);

		SplineMesh->SetStaticMesh(ArcMesh);
		SplineMesh->SetMobility(EComponentMobility::Movable);
		SplineMesh->SetupAttachment(SplineComponent);

		FVector StartPos, StartTangent, EndPos, EndTangent;
		SplineComponent->GetLocalLocationAndTangentAtSplinePoint(i, StartPos, StartTangent);
		SplineComponent->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent);

		SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);

		SplineMesh->RegisterComponent();

		SplineMeshes.Add(SplineMesh);
	}
}

void AMIArcBorder::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Build();
}
