// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameplayWidget.h"
#include "Components/Button.h"


void UABGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (ResumeButton != nullptr)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UABGameplayWidget::OnResumeClicked);
	}

	ReturnToTitlleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (ReturnToTitlleButton != nullptr)
	{
		ReturnToTitlleButton->OnClicked.AddDynamic(this, &UABGameplayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (RetryGameButton != nullptr)
	{
		RetryGameButton->OnClicked.AddDynamic(this, UABGameplayWidget::OnRetryGameClicked);
	}
}

void UABGameplayWidget::OnResumeClicked()
{

}

void UABGameplayWidget::OnReturnToTitleClicked()
{

}

void UABGameplayWidget::OnRetryGameClicked()
{

}
