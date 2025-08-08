#include "PauseScreenWidget.h"
#include "Components/Button.h"

void UPauseScreenWidget::StartNewGame()
{
	OnRestartGame.Broadcast(); // Notify listeners
}

void UPauseScreenWidget::QuitGame()
{
	OnQuitGame.Broadcast(); // Notify listeners
}

void UPauseScreenWidget::PauseGame()
{
	OnPauseGame.Broadcast();
}

void UPauseScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::StartNewGame);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::QuitGame);
	}
	
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::PauseGame);
	}
}
