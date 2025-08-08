#include "GameplayState.h"

void UGameplayState::EnterState(APlayerController* PlayerController)
{

	if (APlayerController* PlayerControllerBase = Cast<APlayerController>(PlayerController))
	{
		// Set input mode and cursor visibility
		PlayerControllerBase->SetInputMode(FInputModeGameOnly());
		PlayerControllerBase->bShowMouseCursor = false;
	}
}

void UGameplayState::ExitState(APlayerController* PlayerController)
{
	
	if (!PlayerController)
	{
		return;
	}
}

void UGameplayState::UpdateState(float DeltaTime)
{
	
}
