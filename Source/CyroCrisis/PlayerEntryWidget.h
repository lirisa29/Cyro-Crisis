#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEntryWidget.generated.h"

UCLASS()
class CYROCRISIS_API UPlayerEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KillCountText;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BackgroundBorder;

	UFUNCTION(BlueprintCallable)
	void SetupEntry(const FString& PlayerName, int32 KillCount, bool bIsHighlighted);
	
};
