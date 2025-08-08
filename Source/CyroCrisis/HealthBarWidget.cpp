#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHealthBarWidget::UpdateHealthBar(float HealthPercentage, const FText& HealthText)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercentage);
	}

	if (HealthTextBlock)
	{
		HealthTextBlock->SetText(HealthText);
	}
}
