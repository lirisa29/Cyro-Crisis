#include "GameManager.h"

#include "GameStateFactory.h"
#include "HUDBase.h"
#include "Kismet/GameplayStatics.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the factory instance
	StateFactory = CreateDefaultSubobject<UGameStateFactory>(TEXT("StateFactory"));

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetFirstPlayerController())
	{
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Escape))
		{
			TogglePause();
		}
	}
}

void AGameManager::ChangeState(EGameState NewState)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController)
	{
		return;
	}

	if (!StateFactory)
	{
		return;
	}

	// Use the factory to create the new state dynamically
	CurrentState = StateFactory->CreateState(NewState);
	
	if (CurrentState)
	{
		switch (NewState)
		{
		case EGameState::Gameplay:
			// Handle Gameplay state: Initialize gameplay UI, set up AI
			OnGameplayState();
			break;
		case EGameState::MatchOver:
			OnMatchOverState();
			break;
		case EGameState::Paused:
			OnPausedState();
			break;
		}
		
		// Enter the new state
		CurrentState->EnterState(PlayerController);
	}
}

void AGameManager::UpdateState(float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->UpdateState(DeltaTime);
	}
}

void AGameManager::OnGameplayState()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
	
	// Set Gameplay HUD visible
	if (HUD)
	{
		HUD->SetGameUIVisibility(true);
		HUD->SetPauseUIVisibility(false);
		HUD->SetGameUIVisibility(false);
	}
}

void AGameManager::OnMatchOverState()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
	
	// Set Gameplay HUD visible
	if (HUD)
	{
		HUD->SetGameUIVisibility(false);
		HUD->SetPauseUIVisibility(false);
		HUD->SetMatchOverUIVisibility(true);
	}
}

void AGameManager::OnPausedState()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
	
	// Set Gameplay HUD visible
	if (HUD)
	{
		HUD->SetGameUIVisibility(false);
		HUD->SetPauseUIVisibility(true);
		HUD->SetMatchOverUIVisibility(false);
	}
}

void AGameManager::TogglePause()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
	
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		ChangeState(EGameState::Gameplay);
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		ChangeState(EGameState::Paused);
	}
}
