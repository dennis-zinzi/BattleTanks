// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		ATankPlayerController();

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
	
	private:
		FORCEINLINE ATank* GetControlledTank() const{
			return Cast<ATank>(GetPawn());
		}

		//Moves barrel to aim towards crosshair
		void AimTowardsCrosshair();

		bool GetSightRayHitLocation(FVector &HitLocation) const;
		bool GetCameraLookDir(const FVector2D &CrosshairLoc, FVector &CameraLookDir) const;
		bool GetCameraLookHitLocation(const FVector &CameraLookDir, FVector &HitLocation) const;

		UPROPERTY(EditAnywhere, Category = "UI")
		float CrosshairLocX;

		UPROPERTY(EditAnywhere, Category = "UI")
		float CrosshairLocY;

		UPROPERTY(EditAnywhere, Category = "Controls")
		float AimRange;

};
