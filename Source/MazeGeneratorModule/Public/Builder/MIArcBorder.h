// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MIArcBorder.generated.h"

class UStaticMesh;

// ArcBorder
// 호모양 Mesh를 가진다
UCLASS()
class MAZEGENERATORMODULE_API AMIArcBorder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMIArcBorder();

	// Spline
	void Build();

	void SetBuildData(double InRadius, double InAngleRadian, int32 InSegments);

private:
	void BuildSpline();
	void BuildArcMesh();

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY(EditAnywhere, Category = "Maze", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, Category = "Maze", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* ArcMesh;

	UPROPERTY(EditAnywhere, Category = "Maze", meta = (AllowPrivateAccess = "true"))
	double Radius = 10.f;

	UPROPERTY(EditAnywhere, Category = "Maze", meta = (AllowPrivateAccess = "true"))
	int32 Segments = 12;

	UPROPERTY(EditAnywhere, Category = "Maze", meta = (AllowPrivateAccess = "true"))
	double AngleRadian;

	UPROPERTY()
	TArray<class USplineMeshComponent*> SplineMeshes;
};
