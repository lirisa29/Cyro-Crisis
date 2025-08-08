#include "GameLayoutBase.h"

#include "DefaultGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UGameLayoutBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Ensure GameManager is accessible by getting it from the current GameMode
	if (!GameManager)
	{
		ADefaultGameModeBase* GameMode = Cast<ADefaultGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameManager = GameMode->GameManager;  // Assign GameManager from GameMode
		}
	}
	
		// Unbind existing delegates first
		MatchOverUI->OnRestartGame.Clear();
		MatchOverUI->OnQuitGame.Clear();

		PauseUI->OnPauseGame.Clear();
		PauseUI->OnRestartGame.Clear();
		PauseUI->OnQuitGame.Clear();

		// Bind to TitleScreenWidget events
		MatchOverUI->OnRestartGame.AddDynamic(this, &UGameLayoutBase::HandleRestartGame);
		MatchOverUI->OnQuitGame.AddDynamic(this, &UGameLayoutBase::HandleQuit);

		PauseUI->OnRestartGame.AddDynamic(this, &UGameLayoutBase::HandleRestartGame);
		PauseUI->OnQuitGame.AddDynamic(this, &UGameLayoutBase::HandleQuit);
		PauseUI->OnPauseGame.AddDynamic(this, &UGameLayoutBase::HandlePause);
	
}

void UGameLayoutBase::HandleRestartGame()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Map/Level1"));
	
	if (GameManager)
	{
		GameManager->ChangeState(EGameState::Gameplay); // Transition to the gameplay state
	}
}

void UGameLayoutBase::HandleQuit()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Map/TitleScreen"));
	
	if (GameManager)
	{
		GameManager->ChangeState(EGameState::TitleScreen); // Transition to the gameplay state
	}
}

void UGameLayoutBase::HandlePause()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	
	if (GameManager)
	{
		GameManager->ChangeState(EGameState::Gameplay);
	}
}
