// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	ABLOG(Warning, TEXT("start"));
	Super::PostInitializeComponents();
	ABLOG(Warning, TEXT("end"));
}

void AABPawn::PossessedBy(AController* NewController)
{
	ABLOG(Warning, TEXT("start"));
	Super::PossessedBy(NewController);
	ABLOG(Warning, TEXT("end"));
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

