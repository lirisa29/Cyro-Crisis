#include "PausedState.h"

void UPausedState::EnterState(APlayerController* PlayerController)
{
	if (APlayerController* PlayerControllerBase = Cast<APlayerController>(PlayerController))
	{
		// Set input mode and cursor visibility
		PlayerControllerBase->SetInputMode(FInputModeUIOnly());
		PlayerControllerBase->bShowMouseCursor = true;
	}
}

void UPausedState::ExitState(APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return;
	}
}

void UPausedState::UpdateState(float DeltaTime)
{
	
}
