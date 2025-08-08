#include "MatchOverWidget.h"

#include "Components/Button.h"

void UMatchOverWidget::StartNewGame()
{
	OnRestartGame.Broadcast(); // Notify listeners
}

void UMatchOverWidget::QuitGame()
{
	OnQuitGame.Broadcast(); // Notify listeners
}

void UMatchOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UMatchOverWidget::StartNewGame);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMatchOverWidget::QuitGame);
	}
}
