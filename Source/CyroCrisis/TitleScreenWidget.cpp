#include "TitleScreenWidget.h"
#include "Components/Button.h"


void UTitleScreenWidget::StartNewGame()
{
	OnStartGame.Broadcast(); // Notify listeners
}

void UTitleScreenWidget::QuitGame()
{
	OnQuitGame.Broadcast(); // Notify listeners
}

void UTitleScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTitleScreenWidget::StartNewGame);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UTitleScreenWidget::QuitGame);
	}
}
