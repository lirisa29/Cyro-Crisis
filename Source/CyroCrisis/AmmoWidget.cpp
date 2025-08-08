#include "AmmoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWidget();
}

// Set the content of the ammo widget, including the gun icon and ammo counts
void UAmmoWidget::SetWidgetContent(const FSlateBrush& NewGunBrush, const FString& MagazineText,
                                   const FString& TotalText)
{
	GunIconBrush = NewGunBrush;

	// Converts the magazine and total ammo text to integers
	CurrentMagazineAmmo = FCString::Atoi(*MagazineText);
	CurrentTotalAmmo = FCString::Atoi(*TotalText);

	UpdateWidget();
}

// Update the ammo values displayed in the widget
void UAmmoWidget::SetAmmoValue(int32 NewMagazineValue, int32 NewTotalValue)
{
	CurrentMagazineAmmo = NewMagazineValue;
	CurrentTotalAmmo = NewTotalValue;

	UpdateWidget();
}

// Update the widget's visual elements to reflect the current ammo values
void UAmmoWidget::UpdateWidget()
{
	if(GunIcon)
	{
		GunIcon->SetBrush(GunIconBrush);
	}

	if(MagazineAmmo)
	{
		MagazineAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentMagazineAmmo)));
	}

	if(TotalAmmo)
	{
		TotalAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentTotalAmmo)));
	}
}
