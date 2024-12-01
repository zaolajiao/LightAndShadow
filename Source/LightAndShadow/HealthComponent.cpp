// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Health = MaxHealth;

	CharacterPlayer= UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player = CharacterPlayer;

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	}
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UHealthComponent::DamageTaken(AActor* DamageActor,float Damage, const UDamageType* DamageType, class AController* Instigator,AActor* DamageCauser)
{
	if(Damage <0.f || Health <=0.f){
		return;
	}
	Health -= Damage;
	if(Health <= 0.f) //&& ToonTanksGameModeBase)
	{
		Health = 0.f;
		// if (GetOwner() == Tank){
		// 	TankDiedHandler();
		// }else{
		// 	ToonTanksGameModeBase->ActorDied(DamageActor);
		// }
	}

	if(Player && DamageActor == Player)
	{
		// if (HealthBar)
		// {
		// 	HealthBar->SetPercent(Health/MaxHealth);
		// 	if(HealthBar && Health/MaxHealth <= 0.5f)
		// 	{
		// 		HealthBar->SetFillColorAndOpacity(FLinearColor::Red);
		// 	}
		// }
	}
}