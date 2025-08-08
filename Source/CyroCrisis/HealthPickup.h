#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickup.generated.h"

class USphereComponent;
class ACharacterBase;

UCLASS()
class CYROCRISIS_API AHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	

	AHealthPickup();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollisionComponent;

	// Rotation values for the pickup's movement
	UPROPERTY(EditAnywhere, Category = Movement)
	float PitchValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float YawValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float RollValue;

	// Default scale for gun mesh
	UPROPERTY()
	FVector DefaultScale = FVector(1.0f, 1.0f, 1.0f);

	// Scale for when method is not in use
	UPROPERTY()
	FVector OpenScale = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	float HealthAmount;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	float RespawnTime;

	FTimerHandle RespawnTimerHandle;

	void Respawn();
	void OnPickedUp();

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
