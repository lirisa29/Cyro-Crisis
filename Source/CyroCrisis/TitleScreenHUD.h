#pragma once

#include "CoreMinimal.h"
#include "TitleScreenLayout.h"
#include "TitleScreenWidget.h"
#include "GameFramework/HUD.h"
#include "TitleScreenHUD.generated.h"

UCLASS()
class CYROCRISIS_API ATitleScreenHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTitleScreenLayout>TitleScreenLayoutClass = nullptr;

	UPROPERTY()
	UTitleScreenWidget* TitleScreenWidget = nullptr;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UWorld>World = nullptr;

	UPROPERTY()
	TObjectPtr<UTitleScreenLayout>TitleScreenLayoutWidget = nullptr;
	
};
