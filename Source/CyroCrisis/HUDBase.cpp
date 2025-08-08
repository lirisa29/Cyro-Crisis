#include "HUDBase.h"

#include "GameLayoutBase.h"
#include "HealthBarWidget.h"

void AHUDBase::BeginPlay()
{
	Super::BeginPlay();
	
	World = GetWorld();
	checkf(World, TEXT( "Failed to reference the world"));
	checkf(GameLayoutBaseClass, TEXT("GameLayoutBase not specified"));

	GameLayoutWidget = CreateWidget<UGameLayoutBase>(World, GameLayoutBaseClass);
	GameLayoutWidget->AddToViewport();
	GameLayoutWidget->SetVisibility(ESlateVisibility::Visible);

	HealthBarWidget = Cast<UHealthBarWidget>(GameLayoutWidget->HealthBar);
	AmmoWidget = Cast<UAmmoWidget>(GameLayoutWidget->AmmoUI);
	TimerWidget = Cast<UTimerWidget>(GameLayoutWidget->TimerUI);
	PauseWidget = Cast<UPauseScreenWidget>(GameLayoutWidget->PauseUI);
	MatchOverWidget = Cast<UMatchOverWidget>(GameLayoutWidget->MatchOverUI);

	// Set visibility using methods to ensure consistency
	SetGameUIVisibility(true);  // Hide game UI
	SetPauseUIVisibility(false);
	SetMatchOverUIVisibility(false);
}

void AHUDBase::SetAmmo(int32 Magazine, int32 Total)
{
	if (GameLayoutWidget && GameLayoutWidget->AmmoUI)
	{
		GameLayoutWidget->AmmoUI->SetAmmoValue(Magazine, Total);
	}
}

void AHUDBase::SetGameUIVisibility(bool bIsVisible)
{
	if (GameLayoutWidget)
	{
		ESlateVisibility Visibility = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

		if (HealthBarWidget)
		{
			HealthBarWidget->SetVisibility(Visibility);
		}

		if (AmmoWidget)
		{
			AmmoWidget->SetVisibility(Visibility);
		}

		if (TimerWidget)
		{
			TimerWidget->SetVisibility(Visibility);
		}
	}
}

void AHUDBase::UpdateMatchTimerDisplay(int32 TimeRemaining)
{
	if (TimerWidget)
	{
		TimerWidget->UpdateTimerDisplay(TimeRemaining);
	}
}

void AHUDBase::SetPauseUIVisibility(bool bIsVisible)
{
	if (GameLayoutWidget)
	{
		ESlateVisibility Visibility = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

		if (PauseWidget)
		{
			PauseWidget->SetVisibility(Visibility);
		}
	}
}

void AHUDBase::SetMatchOverUIVisibility(bool bIsVisible)
{
	if (GameLayoutWidget)
	{
		ESlateVisibility Visibility = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

		if (MatchOverWidget)
		{
			MatchOverWidget->SetVisibility(Visibility);
		}
	}
}

