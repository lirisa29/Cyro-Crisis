#pragma once

#include "CoreMinimal.h"
#include "WeaponsBase.h"
#include "PrimaryWeapon.generated.h"

UCLASS()
class CYROCRISIS_API APrimaryWeapon : public AWeaponsBase
{
	GENERATED_BODY()

public:
	APrimaryWeapon();

protected:
	void Fire() override;
	
};
