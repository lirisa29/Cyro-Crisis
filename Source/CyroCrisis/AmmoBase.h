#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "AmmoBase.generated.h"

// Delegate declaration for pickup triggered events, passing the pickup instance
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickupTriggeredSignature, AAmmoBase* pickup)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAIPickupTriggered, AAmmoBase * pickup)

UCLASS()
class CYROCRISIS_API AAmmoBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAmmoBase();

	// Static delegate instance for broadcasting pickup events
	static FOnPickupTriggeredSignature OnPickupTriggeredDelagate;

	static FOnAIPickupTriggered OnAIPickupTriggeredDelagate;

	// Sphere component used for collision detection
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "0_Setup")
	USphereComponent* SphereTrigger = nullptr;

	// Rotation values for the pickup's movement
	UPROPERTY(EditAnywhere, Category = Movement)
	float PitchValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float YawValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float RollValue;

	// Function called when another component begins overlapping this pickup
	UFUNCTION()
	void OnBeginOverlp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	// Getter function to retrieve the current ammo amount
	int32 GetAmmoAmount() const {return ammoAmount; }

protected:
	virtual void BeginPlay() override;

	// Amount of ammo provided by this pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int ammoAmount;

public:	
	virtual void Tick(float DeltaTime) override;

};
