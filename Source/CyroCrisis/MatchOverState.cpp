#include "MatchOverState.h"

void UMatchOverState::EnterState(APlayerController* PlayerController)
{
	if (APlayerController* PlayerControllerBase = Cast<APlayerController>(PlayerController))
	{
		// Set input mode and cursor visibility
		PlayerControllerBase->SetInputMode(FInputModeUIOnly());
		PlayerControllerBase->bShowMouseCursor = true;
	}
}

void UMatchOverState::ExitState(APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return;
	}
}

void UMatchOverState::UpdateState(float DeltaTime)
{
	
}
