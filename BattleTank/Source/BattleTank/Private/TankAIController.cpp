// Łukasz Kandziora 2018. All rights reserved.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller possesing %s"), *tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Tank to posses"), *GetName());
	}

	ATank* playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller now targeting player %s"), *playerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s did could not find any player to target"), *GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	ATank* tank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();
	if (playerTank && tank)
	{
		tank->AimAt(playerTank->GetActorLocation());
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	UWorld* world = GetWorld();
	if (world)
	{
		APlayerController* playerController = world->GetFirstPlayerController();
		if (playerController)
		{
			APawn* playerPawn = playerController->GetPawn();
			if (playerPawn)
			{
				return Cast<ATank>(playerPawn);
			}
		}
	}
	return nullptr;
}