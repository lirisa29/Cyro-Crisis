#include "TitleScreenLayout.h"

#include "TitleScreenGameMode.h"
#include "Kismet/GameplayStatics.h"

void UTitleScreenLayout::NativeConstruct()
{
	Super::NativeConstruct();

	// Ensure GameManager is accessible by getting it from the current GameMode
	if (!GameManager)
	{
		ATitleScreenGameMode* GameMode = Cast<ATitleScreenGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameManager = GameMode->GameManager;  // Assign GameManager from GameMode
		}
	}
		
		// Unbind existing delegates first
		TitleScreenUI->OnStartGame.Clear();
		TitleScreenUI->OnQuitGame.Clear();

		// Bind to TitleScreenWidget events
		TitleScreenUI->OnStartGame.AddDynamic(this, &UTitleScreenLayout::HandleStartGame);
		TitleScreenUI->OnQuitGame.AddDynamic(this, &UTitleScreenLayout::HandleQuit);
}

void UTitleScreenLayout::HandleStartGame()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Map/Level1"));
	
	if (GameManager)
	{
		GameManager->ChangeState(EGameState::Gameplay); // Transition to the gameplay state
	}
}

void UTitleScreenLayout::HandleQuit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
