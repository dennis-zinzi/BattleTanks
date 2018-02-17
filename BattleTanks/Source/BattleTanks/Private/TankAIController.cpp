// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay(){
	Super::BeginPlay();

	ATank *tank = GetControlledTank();
	if(tank){
		UE_LOG(LogTemp, Warning, TEXT("AI Tank (%s) is possessed"), *tank->GetName());
	}

	ATank *playerTank = GetPlayerTank();
	if(playerTank){
		UE_LOG(LogTemp, Warning, TEXT("Player Tank %s, found!"), *playerTank->GetName());
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank NOT found!"));
	}
}


void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//TODO Move towards player

	//Check tank is possessed
	ATank *tank = GetControlledTank();
	if(tank){
		//Get player tank
		ATank *playerTank = GetPlayerTank();
		if(playerTank){
			//Aim at player
			tank->AimAt(playerTank->GetActorLocation());
		}
	}

	//Fire at player if ready to
}
