// Łukasz Kandziora 2018. All rights reserved.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	//Start the tank moving the barrel so that a shot would hit
	//where the crosshair intersects the world
	void AimTowardsCrosshair();

	bool RaycastForwardThroughCrosshair(FHitResult& hitResult) const;
	void DeprojectCrosshairPositionToWorld(FVector& location, FVector& direction) const;

	UUserWidget* userWidget = nullptr;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = .5f;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = .33333f;
};