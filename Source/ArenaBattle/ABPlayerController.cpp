// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"


void AABPlayerController::PostInitializeComponents()
{
	ABLOG(Warning, TEXT("start"));
	Super::PostInitializeComponents();
	ABLOG(Warning, TEXT("end"));
}

void AABPlayerController::Possess(APawn* aPawn)
{
	ABLOG(Warning,TEXT("start"));
	Super::Possess(aPawn);
	ABLOG(Warning, TEXT("end"));
}

