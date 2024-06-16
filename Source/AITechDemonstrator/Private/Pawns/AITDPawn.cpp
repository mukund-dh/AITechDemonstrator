// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/AITDPawn.h"

// Sets default values
AAITDPawn::AAITDPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAITDPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAITDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAITDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

