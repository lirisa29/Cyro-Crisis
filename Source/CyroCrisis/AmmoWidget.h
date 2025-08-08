#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "Components/TextBlock.h"
#include "AmmoWidget.generated.h"

// Forward declaration
class UImage;

UCLASS()
class CYROCRISIS_API UAmmoWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	// Bound widget for the gun icon
	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta=(BindWidget))
	TObjectPtr<UImage>GunIcon = nullptr;

	// Bound widget for displaying magazine ammo count
	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta=(BindWidget))
	TObjectPtr<UTextBlock>MagazineAmmo = nullptr;

	// Bound widget for displaying total ammo count
	UPROPERTY(BlueprintReadOnly, Category = "Bound Widgets", meta=(BindWidget))
	TObjectPtr<UTextBlock>TotalAmmo = nullptr;

private:
	// Brush for the gun icon
	UPROPERTY(EditAnywhere, Category="0_Setup")
	FSlateBrush GunIconBrush;

	// Current amount of ammo in the magazine
	UPROPERTY(EditAnywhere, Category="0_Setup")
	int32 CurrentMagazineAmmo = 0;

	// Current total amount of ammo available
	UPROPERTY(EditAnywhere, Category="0_Setup")
	int32 CurrentTotalAmmo = 0;

	void UpdateWidget();

public:
	// Function to set the widget content
	UFUNCTION(BlueprintCallable, Category = "Widget Update")
	void SetWidgetContent(const FSlateBrush& NewGunBrush, const FString& MagazineText, const FString& TotalText);

	// Function to update the ammo values displayed in the widget
	void SetAmmoValue(int32 NewMagazineValue, int32 NewTotalValue);
};
