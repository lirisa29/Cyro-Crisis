#include "TitleScreenHUD.h"

void ATitleScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	checkf(World, TEXT( "Failed to reference the world"));
	checkf(TitleScreenLayoutClass, TEXT("GameLayoutBase not specified"));

	TitleScreenLayoutWidget = CreateWidget<UTitleScreenLayout>(World, TitleScreenLayoutClass);
	TitleScreenLayoutWidget->AddToViewport();
	TitleScreenLayoutWidget->SetVisibility(ESlateVisibility::Visible);

	TitleScreenWidget = Cast<UTitleScreenWidget>(TitleScreenLayoutWidget->TitleScreenUI);
}
