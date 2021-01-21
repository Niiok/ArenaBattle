// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterWidget.h"
#include "ABCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UABCharacterWidget::BindCharacterStat(UABCharacterStatComponent* NewCharacterStat)
{
	ABCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;
	/*
	NewCharacterStat->OnHPChanged.AddLambda(
		[this]() -> void {
			if (CurrentCharacterStat.IsValid())
			{
				ABLOG(Warning, TEXT("HPRatio : %f"), CurrentCharacterStat->GetHPRatio());
			}
		}
	);*/

	NewCharacterStat->OnHPChanged.AddUObject(this, &UABCharacterWidget::UpdateHPWidget);
}

void UABCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ABCHECK(HPProgressBar != nullptr);
	UpdateHPWidget();
}

void UABCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}