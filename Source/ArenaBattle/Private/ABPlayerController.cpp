// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"
#include "ABCharacterStatComponent.h"


AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

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

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UABHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	ABPlayerState = Cast<AABPlayerState>(PlayerState);
	//auto ABPlayerState = Cast<AABPlayerState>(PlayerState);  //In-Function variable
	ABCHECK(ABPlayerState != nullptr);
	HUDWidget->BindPlayerState(ABPlayerState);
	ABPlayerState->OnPlayerStateChanged.Broadcast();
}

void  AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AABPlayerController::OnGamePause);
}

void AABPlayerController::OnGamePause()
{

}

UABHUDWidget* AABPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void AABPlayerController::NPCKill(AABCharacter* KilledNPC) const
{
	if (ABPlayerState->AddExp(KilledNPC->GetExp()))
	{
		auto Stat = Cast<AABCharacter>(GetPawn())->CharacterStat;
		ABCHECK(Stat != nullptr);
		Stat->SetNewLevel(ABPlayerState->GetCharacterLevel());
	}
}

void AABPlayerController::AddGameScore() const
{
	ABPlayerState->AddGameScore();
}