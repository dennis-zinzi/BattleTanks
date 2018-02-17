// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATankPlayerController::ATankPlayerController(){
	CrosshairLocX = 0.5f;
	CrosshairLocY = 1.0f / 3.0f;
	AimRange = 1000000.0f;
}


void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();

	ATank *tank = GetControlledTank();
	if(tank){
		UE_LOG(LogTemp, Warning, TEXT("Tank is possessed"));
	}
}


void ATankPlayerController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair(){
	if(!GetControlledTank())
		return;

	//Get location of linetrace through crosshair
	FVector HitLoc;
	
	//If hits landscape
	if(GetSightRayHitLocation(HitLoc)){
		//Tell controlled tank to aim barrel at location
		GetControlledTank()->AimAt(HitLoc);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const{
	//Get viewport dimensions
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//Find crosshair location in sceen coords
	FVector2D CrosshairLoc(ViewportSizeX * CrosshairLocX, ViewportSizeY * CrosshairLocY);

	FVector CameraLookDir;
	//Find camera look direction based on crosshair location
	if(GetCameraLookDir(CrosshairLoc, CameraLookDir)){
		//Create line trace to find any hits
		return GetCameraLookHitLocation(CameraLookDir, HitLocation);
	}
	
	return false;
}


bool ATankPlayerController::GetCameraLookDir(const FVector2D &CrosshairLoc, FVector &CameraLookDir) const{
	//Value not used but needed for Deproject method
	FVector CameraWorldLoc;
	return DeprojectScreenPositionToWorld(CrosshairLoc.X, CrosshairLoc.Y, CameraWorldLoc, CameraLookDir);
}


bool ATankPlayerController::GetCameraLookHitLocation(const FVector &CameraLookDir, FVector &HitLocation) const{
	//Calculate line trace end points
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = Start + (CameraLookDir * AimRange);

	FHitResult HitRes;

	//Make Line trace
	if(GetWorld()->LineTraceSingleByChannel(HitRes, Start, LineTraceEnd, ECC_Visibility)){
		HitLocation = HitRes.Location;
		return true;
	}

	//Line trace failed
	return false;
}
