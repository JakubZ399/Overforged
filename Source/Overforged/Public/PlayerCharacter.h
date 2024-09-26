#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class OVERFORGED_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputMove;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputDash;
	
	void Move(const FInputActionValue& Value);
	void Dash();

private:


	//Dash
	UPROPERTY(EditInstanceOnly, Category = "Movement")
	float DashDistance = 2.f;
	bool isDashing = false;
	FTimerHandle DashTimerHandle;
	void StopDashing();
};
