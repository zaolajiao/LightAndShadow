// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightAndShadowGameMode.h"
#include "LightAndShadowCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALightAndShadowGameMode::ALightAndShadowGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
