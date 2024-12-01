// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBaseActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/BoxComponent.h"
#include "LightAndShadowCharacter.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALightBaseActor::ALightBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
    SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
    SpotLight->SetupAttachment(RootComponent);
    SpotLight->SetLightColor(FLinearColor::White);
    SpotLight->SetIntensity(5000.0f);
    SpotLight->SetInnerConeAngle(20.0f);
    SpotLight->SetOuterConeAngle(40.0f);

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ALightBaseActor::BeginPlay()
{
	Super::BeginPlay();
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightBaseActor::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALightBaseActor::OnOverlapEnd);
                UE_LOG(LogTemp, Warning, TEXT("Begin Begin Begin"));
}

// Called every frame
void ALightBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                bool bFromSweep, const FHitResult& SweepResult)
{


    if (OtherActor && OtherActor != this)
    {
        ALightAndShadowCharacter* Character = Cast<ALightAndShadowCharacter>(OtherActor);
        if (Character)
        {
            Character->LightCounter++;
                    UE_LOG(LogTemp, Warning, TEXT("Character->LightCounter++: %d"), Character->LightCounter);
            if(Character->LightCounter > 0)
            {
                Character->StartLightTimer();
            }
        }

        AEnemyCharacter* enemyCharacter = Cast<AEnemyCharacter>(OtherActor);
        if (enemyCharacter)
        {
        	if(DestroyEffect)
            {
                UGameplayStatics::SpawnEmitterAtLocation(
                    GetWorld(),
                    DestroyEffect,
                    enemyCharacter->GetActorLocation(),
                    FRotator::ZeroRotator,
                    FVector(0.1f)
                );
            }
            enemyCharacter->Destroy();
        }
    }
}

void ALightBaseActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this)
    {
        ALightAndShadowCharacter* Character = Cast<ALightAndShadowCharacter>(OtherActor);
        if (Character)
        {
            if(Character->LightCounter>0)
            {
                 Character->LightCounter--;
 UE_LOG(LogTemp, Warning, TEXT("Character->LightCounter--: %d"), Character->LightCounter);
                if(Character->LightCounter == 0)
                {
                    Character->StopLightTimer();
                }
            }     
        }
    }
}