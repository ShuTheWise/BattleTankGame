// Łukasz Kandziora 2018. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(BattleTank), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector location, float launchSpeed);

	void SetBarrelReference(UTankBarrel * BarrelToSet);

private:	

	UTankBarrel* Barrel = nullptr;

	void MoveBarrel(FVector AimDirection);
};
