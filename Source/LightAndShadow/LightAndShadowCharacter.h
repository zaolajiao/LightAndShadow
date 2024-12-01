// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "LightAndShadowCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ALightAndShadowCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ALightAndShadowCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Health=10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MaxHealth=10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Dark=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 DarkLimit=3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
	int32 LightCounter=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
	int32 ShadowCounter=0;

	UFUNCTION(BlueprintCallable, Category = "Counter")
	void AddLightCounter();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void DecLightCounter();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void AddShadowCounter();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void DecShadowCounter();


    FTimerHandle LightTimerHandle;
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void StartLightTimer();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void StopLightTimer();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void DecDark();

    FTimerHandle ShadowTimerHandle;
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void StartShadowTimer();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void StopShadowTimer();
	UFUNCTION(BlueprintCallable, Category = "Counter")
	void AddDark();

	UFUNCTION(BlueprintCallable, Category = "Counter")
	void SpawnCharacterAfterDelay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
	TSubclassOf<class AEnemyCharacter> CharacterToSpawn;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* CascadeEffect;

	UFUNCTION(BlueprintCallable, Category = "Counter")
	void CreateDark();

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
    UPROPERTY(EditAnywhere, Category = "TakeDamage")
    UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, Category = "TakeDamage")
	USoundBase* PainSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    class UHealthComponent* HealthComponent;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameOver")
    TSubclassOf<UUserWidget> WidgetClass;

private:
    FVector CurrentLocation = GetActorLocation();
	UParticleSystemComponent* ParticleComponent;
	FCriticalSection Mutex;
    void StartTimer();
	void StopTimer();
	void GameOver();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

