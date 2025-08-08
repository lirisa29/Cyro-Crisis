#include "SecondaryGun.h"

ASecondaryGun::ASecondaryGun()
{
	WeaponName = "Secondary Weapon";
	WeaponMaxAmmo = 20;
	MagazineMaxAmmo = 6;
	BaseDamage = 12.0f;

	CurrentTotalAmmo = WeaponMaxAmmo;
	CurrentMagazineAmmo = MagazineMaxAmmo;
}

bool ASecondaryGun::IsSecondaryWeapon() const
{
	return true;
}
