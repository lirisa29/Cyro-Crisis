#include "TitleScreenGameMode.h"

void ATitleScreenGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialise the GameManager to handle state transitions
	GameManager = GetWorld()->SpawnActor<AGameManager>(AGameManager::StaticClass());

	if (GameManager)
	{
		// Start the game by transitioning to title screen
		GameManager->ChangeState(EGameState::TitleScreen);
	}
}
