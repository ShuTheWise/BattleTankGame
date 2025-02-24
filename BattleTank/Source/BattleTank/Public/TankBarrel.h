// Łukasz Kandziora 2018. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds barrel's properties and Elevate method
 */
UCLASS(ClassGroup = (BattleTank), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 20.f;

	UPROPERTY(EditAnywhere)
		float MinElevationInDegrees = -20.f;

	UPROPERTY(EditAnywhere)
		float MaxElevationInDegrees = 40.f;
};
