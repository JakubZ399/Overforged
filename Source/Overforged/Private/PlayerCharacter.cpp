#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(InputDash, ETriggerEvent::Triggered, this, &APlayerCharacter::Dash);
		EnhancedInputComponent->BindAction(InputPauseMenu, ETriggerEvent::Triggered, this, &APlayerCharacter::OpenPauseMenu);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, MovementVector.Y);
	AddMovementInput(RightVector, MovementVector.X);
}

void APlayerCharacter::Dash()
{
	if (!isDashing)
	{
		isDashing = true;

		FVector PlayerVelocity = GetVelocity() * DashDistance;
		FVector PlayerVelocityXY(PlayerVelocity.X, PlayerVelocity.Y, 0.f);

		LaunchCharacter(PlayerVelocityXY, false, false);

		GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &APlayerCharacter::StopDashing, 1.f, false);
	}
}

void APlayerCharacter::StopDashing()
{
	isDashing = false;
}

void APlayerCharacter::OpenPauseMenu()
{
	UUserWidget* PauseMenu = CreateWidget(GetWorld(), PauseMenuWidget);

	if (PauseMenu)
	{
		PauseMenu->AddToViewport();
	}
}