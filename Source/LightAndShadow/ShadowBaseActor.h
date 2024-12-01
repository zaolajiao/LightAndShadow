// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShadowBaseActor.generated.h"

UCLASS()
class LIGHTANDSHADOW_API AShadowBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShadowBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta =(AllowPrivateAccess = "true"))
    class UBoxComponent* BoxComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable)
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                        bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION(BlueprintCallable)
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
