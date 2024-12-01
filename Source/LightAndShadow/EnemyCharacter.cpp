// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "LightAndShadowCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ALightAndShadowCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	GetWorldTimerManager().SetTimer(EnemyMoveRateTimerHandle, this, &AEnemyCharacter::CheckMoveCondition, 1.0f, true);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to inputd
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::CheckMoveCondition()
{
	if(PlayerCharacter)
	{
		if(InWalkingRange())
		{
			MoveToPlayer();
		}
	}
}

bool AEnemyCharacter::InWalkingRange()
{
	if(PlayerCharacter)
	{
		float Distance = FVector::Dist(PlayerCharacter->GetActorLocation(), GetActorLocation());
		if(Distance < WalkingRange)
		{
			return true;
		}
	}
	return false;
}

void AEnemyCharacter::MoveToPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveToPlayer"));
	if(PlayerCharacter)
	{
		FVector Direction = PlayerCharacter->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter->GetActorLocation(): %s"), *PlayerCharacter->GetActorLocation().ToString());
			        UE_LOG(LogTemp, Warning, TEXT("GetActorLocation(): %s"), * GetActorLocation().ToString());
	        UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString());
		AddMovementInput(Direction, 2.0f);
	}
}
