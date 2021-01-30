// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"
#include "ABCharacterStatComponent.h"
#include "ABGameplayWidget.h"
#include "ABGameplayResultWidget.h"
#include "ABGameState.h"


AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UABGameplayWidget> UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UABGameplayResultWidget> UI_RESULT_C(TEXT("/Game/Book/UI/UI_Result.UI_Result_C"));
	if (UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass = UI_RESULT_C.Class;
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

	ChangeInputMode(true);
	//FInputModeGameOnly InputMode;
	//SetInputMode(InputMode);

	HUDWidget = CreateWidget<UABHUDWidget>(this, HUDWidgetClass);
	ABCHECK(HUDWidget != nullptr);
	HUDWidget->AddToViewport(1);

	ResultWidget = CreateWidget<UABGameplayResultWidget>(this, ResultWidgetClass);
	ABCHECK(ResultWidget != nullptr);

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
	MenuWidget = CreateWidget<UABGameplayWidget>(this, MenuWidgetClass);
	ABCHECK(MenuWidget != nullptr);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
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

void AABPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInpuMode);
		bShowMouseCursor = true;
	}
}

void AABPlayerController::ShowResultUI()
{
	auto ABGameState = Cast<AABGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(ABGameState != nullptr);
	ResultWidget->BindGameState(ABGameState);

	ResultWidget->AddToViewport(); //add on viewport with higher Z may needed
	ChangeInputMode(false);
}