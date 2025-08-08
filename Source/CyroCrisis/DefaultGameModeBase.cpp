#include "DefaultGameModeBase.h"

#include "HUDBase.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "Containers/Array.h"
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "RespawnPoint.h"
#include "Kismet/GameplayStatics.h"

void ADefaultGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialise the GameManager to handle state transitions
	GameManager = GetWorld()->SpawnActor<AGameManager>(AGameManager::StaticClass());

	if (GameManager)
	{
		// Start the game by transitioning to title screen
		GameManager->ChangeState(EGameState::Gameplay);
	}

	TArray<AActor*> RespawnPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARespawnPoint::StaticClass(), RespawnPointActors);

	for (AActor* Actor : RespawnPointActors)
	{
		ARespawnPoint* RespawnPoint = Cast<ARespawnPoint>(Actor);
		if (RespawnPoint)
		{
			RespawnLocations.Add(RespawnPoint);
		}
	}

	StartMatchTimer();
}

void ADefaultGameModeBase::OnMatchEnd()
{
	if (!GameManager)
	{
		return;
	}
	
	if (GameManager)
	{
		GameManager->ChangeState(EGameState::MatchOver);
	}
}

void ADefaultGameModeBase::EndGame()
{
	GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	OnMatchEnd();
}

void ADefaultGameModeBase::RespawnPlayer(ACharacterBase* PlayerCharacter)
{
	if (!PlayerCharacter || RespawnLocations.Num() == 0)
		return;

	// Maximum attempts to find a free location (to avoid infinite loops)
	const int32 MaxAttempts = 10;

	int32 Attempts = 0;
	bool bLocationFound = false;
	FVector SpawnLocation;

	while (Attempts < MaxAttempts && !bLocationFound)
	{
		// Choose a random respawn location
		int32 Index = FMath::RandRange(0, RespawnLocations.Num() - 1);
		AActor* RespawnActor = RespawnLocations[Index];

		if (RespawnActor)
		{
			SpawnLocation = RespawnActor->GetActorLocation();

			// Assuming the location is always free (since overlap checks are removed)
			bLocationFound = true; 
		}

		Attempts++;
	}

	if (bLocationFound)
	{
		// Respawn player
		PlayerCharacter->SetActorLocation(SpawnLocation);
		PlayerCharacter->ResetPlayerHealth();
	}
	else
	{
		return;
	}
}

void ADefaultGameModeBase::RespawnBot(AAICharacter* BotCharacter)
{
	if (!BotCharacter || RespawnLocations.Num() == 0)
		return;

	const int32 MaxAttempts = 10;

	int32 Attempts = 0;
	bool bLocationFound = false;
	FVector SpawnLocation;

	while (Attempts < MaxAttempts && !bLocationFound)
	{
		// Choose a random respawn location
		int32 Index = FMath::RandRange(0, RespawnLocations.Num() - 1);
		AActor* RespawnActor = RespawnLocations[Index];

		if (RespawnActor)
		{
			SpawnLocation = RespawnActor->GetActorLocation();

			// Assuming the location is always free (since overlap checks are removed)
			bLocationFound = true; 
		}
		Attempts++;
	}

	if (bLocationFound)
	{
		// Respawn bot
		BotCharacter->SetActorLocation(SpawnLocation);
		BotCharacter->ResetBotHealth();
	}
	else
	{
		return;
	}
}

void ADefaultGameModeBase::StartMatchTimer()
{
	MatchTimeRemaining = 300; // 5 minutes in seconds
	GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &ADefaultGameModeBase::UpdateMatchTimer, 1.0f, true);
}

void ADefaultGameModeBase::UpdateMatchTimer()
{
	if (MatchTimeRemaining > 0)
	{
		MatchTimeRemaining--;

		// Update UI (Broadcast to HUD)
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
			if (HUD)
			{
				HUD->UpdateMatchTimerDisplay(MatchTimeRemaining);
			}
		}
	}
	else
	{
		EndGame();
	}
}
