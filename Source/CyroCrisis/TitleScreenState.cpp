#include "TitleScreenState.h"

void UTitleScreenState::EnterState(APlayerController* PlayerController)
{
		if (APlayerController* PlayerControllerBase = Cast<APlayerController>(PlayerController))
		{
			// Set input mode and cursor visibility
			PlayerControllerBase->SetInputMode(FInputModeUIOnly());
			PlayerControllerBase->bShowMouseCursor = true;
		}
}

void UTitleScreenState::ExitState(APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return;
	}
}

void UTitleScreenState::UpdateState(float DeltaTime)
{
	
}
