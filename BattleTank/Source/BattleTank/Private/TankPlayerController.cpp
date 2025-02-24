// Łukasz Kandziora 2018. All rights reserved.

#include "TankPlayerController.h"

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller possesing %s"), *tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Tank to posses"), *GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto tank = GetControlledTank();
	if (!tank)
	{
		return;
	}

	FHitResult  fhitResult;

	// Get line-trace hit location (through crosshair)
	if (RaycastForwardThroughCrosshair(fhitResult))
	{
		FVector hitLocation = fhitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Raycast hit %s at location {%s}"), *fhitResult.GetActor()->GetName(), *hitLocation.ToString());

		// Tell controlled tank to aim at line-trace hit location

		tank->AimAt(hitLocation);
	}
}

bool ATankPlayerController::RaycastForwardThroughCrosshair(FHitResult& fhitResult) const
{
	FVector start;
	FVector end;
	FVector dir;

	//Getting crosshair's world location and direction
	DeprojectCrosshairPositionToWorld(start, dir);

	//line trace end vector
	end = start + dir * LineTraceRange;

	//DrawDebugLine(GetWorld(), start, end, FColor(255, 0, 0), false, -1, 0, 5.f);
	return GetWorld()->LineTraceSingleByChannel(fhitResult, start, end, ECC_Visibility);
}

void ATankPlayerController::DeprojectCrosshairPositionToWorld(FVector &location, FVector &direction)const
{
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, location, direction);
}