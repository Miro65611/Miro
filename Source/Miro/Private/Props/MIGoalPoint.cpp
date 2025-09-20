// Fill out your copyright notice in the Description page of Project Settings.

#include "Props/MIGoalPoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/MICharacter.h"
#include "Net/UnrealNetwork.h"
#include "Miro/Miro.h"

// Sets default values
AMIGoalPoint::AMIGoalPoint()
	:PlayerCount(0)
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;

	PlayerCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerCheckBox"));
	PlayerCheckBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	SetRootComponent(PlayerCheckBox);

	GoalPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalPointMesh"));
	GoalPointMesh->SetupAttachment(PlayerCheckBox);
}

// Called when the game starts or when spawned
void AMIGoalPoint::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerCheckBox && HasAuthority())
	{
		PlayerCheckBox->OnComponentBeginOverlap.AddDynamic(this, &AMIGoalPoint::OnOverlapBegin);
		PlayerCheckBox->OnComponentEndOverlap.AddDynamic(this, &AMIGoalPoint::OnOverlapEnd);
	}
}

void AMIGoalPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugString(GetWorld(), GetActorLocation(), *FString::Printf(TEXT("Player: %d"), PlayerCount), nullptr, FColor::White, 0.0f, false, 1.f);
}

void AMIGoalPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMIGoalPoint, PlayerCount);
}

void AMIGoalPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMICharacter* Character = Cast<AMICharacter>(OtherActor); Character)
	{
		++PlayerCount;
	}
}

void AMIGoalPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMICharacter* Character = Cast<AMICharacter>(OtherActor); Character)
	{
		--PlayerCount;
	}

}

bool AMIGoalPoint::CanInteractable() const
{
	return true;
}

void AMIGoalPoint::OnInteract(AActor* InstigatorActor)
{
	if (CanInteractable() == false)
	{
		return;
	}

	OnNextStageButtonPressed.Broadcast();
}

void AMIGoalPoint::OnHighlightBegin(AActor* InstigatorActor)
{
}

void AMIGoalPoint::OnHighlightEnd(AActor* InstigatorActor)
{
}


