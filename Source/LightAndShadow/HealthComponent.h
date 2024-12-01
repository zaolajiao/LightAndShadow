// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIGHTANDSHADOW_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	class ACharacter* CharacterPlayer;
	class AActor* Player;
	float Health =0.f;
	// class AToonTanksGameModeBase* ToonTanksGameModeBase;
	// class UToonTankGameInstance* ToonTankGameInstance;

	UFUNCTION()
	void DamageTaken(AActor* DamageActor,float Damage, const UDamageType* DamageType, class AController* Instigator,AActor* DamageCauser);

	UPROPERTY(EditAnyWhere)
	float MaxHealth =100.f;
	// UPROPERTY(EditAnywhere,Category ="Combat")
	// TSubclassOf<class UUserWidget> HPGaugeWidget;
	// UPROPERTY(EditAnywhere,Category ="Combat")
	// TSubclassOf<class UUserWidget> GameOverWidget;
	// UPROPERTY(EditAnywhere,Category ="Combat")
	// class  UProgressBar* HealthBar;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
