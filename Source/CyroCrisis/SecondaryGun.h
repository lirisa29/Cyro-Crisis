#pragma once

#include "CoreMinimal.h"
#include "WeaponsBase.h"
#include "SecondaryGun.generated.h"

UCLASS()
class CYROCRISIS_API ASecondaryGun : public AWeaponsBase
{
	GENERATED_BODY()

public:
	ASecondaryGun();

	virtual bool IsSecondaryWeapon() const override;
	
};
