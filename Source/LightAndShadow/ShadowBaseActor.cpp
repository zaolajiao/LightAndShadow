// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowBaseActor.h"
#include "Components/BoxComponent.h"
#include "LightAndShadowCharacter.h"
// Sets default values
AShadowBaseActor::AShadowBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AShadowBaseActor::BeginPlay()
{
	Super::BeginPlay();
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AShadowBaseActor::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AShadowBaseActor::OnOverlapEnd);
                UE_LOG(LogTemp, Warning, TEXT("Begin Begin Begin"));
}

// Called every frame
void AShadowBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShadowBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                bool bFromSweep, const FHitResult& SweepResult)
{

    if (OtherActor && OtherActor != this)
    {
        ALightAndShadowCharacter* Character = Cast<ALightAndShadowCharacter>(OtherActor);
        if (Character)
        {
            Character->ShadowCounter++;
         UE_LOG(LogTemp, Warning, TEXT("Character->ShadowCounter++: %d"), Character->ShadowCounter);
            	UE_LOG(LogTemp, Warning, TEXT("Character->LightCounter: %d"), Character->LightCounter);
            if(Character->ShadowCounter > 0 && Character->LightCounter==0)
            {
                Character->StartShadowTimer();
            }
        }
    }
}

void AShadowBaseActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this)
    {
        ALightAndShadowCharacter* Character = Cast<ALightAndShadowCharacter>(OtherActor);
        if (Character)
        {
            if(Character->ShadowCounter>0)
            {
                 Character->ShadowCounter--;
                     UE_LOG(LogTemp, Warning, TEXT("Character->ShadowCounter--: %d"), Character->ShadowCounter);
                 if(Character->ShadowCounter == 0)
                 {
                     Character->StopShadowTimer();
                 }
            }     
        }
    }
}