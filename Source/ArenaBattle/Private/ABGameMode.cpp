// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameMode.h"
#include "ABCharacter.h"
#include "ABPlayerController.h"
#include "ABPlayerState.h"
#include "ABGameState.h"

AABGameMode::AABGameMode()
{
	DefaultPawnClass = AABCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
	PlayerStateClass = AABPlayerState::StaticClass();
	GameStateClass = AABGameState::StaticClass();
}

void AABGameMode::PostLogin(APlayerController * NewPlayer)
{
	ABLOG(Warning, TEXT("start"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("end"));

	auto ABPlayerState = Cast<AABPlayerState>(NewPlayer->PlayerState);
	ABCHECK(ABPlayerState != nullptr);
	ABPlayerState->InitPlayerData();
}

void AABGameMode::PostInitializeComponents()
{
	ABLOG(Warning, TEXT("start"));
	Super::PostInitializeComponents();
	ABLOG(Warning, TEXT("end"));

	ABGameState = Cast<AABGameState>(GameState);
}

void AABGameMode::AddScore(AABPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto ABPlayerController = Cast<AABPlayerController>(It->Get());
		if ((ABPlayerController != nullptr) && (ScoredPlayer == ABPlayerController))
		{
			ABPlayerController->AddGameScore();
			break;
		}
	}

	ABGameState->AddGameScore();
}


