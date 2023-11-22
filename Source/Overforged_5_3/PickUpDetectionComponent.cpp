// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpDetectionComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

class APickUp;
// Sets default values for this component's properties
UPickUpDetectionComponent::UPickUpDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickUpDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPickUpDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetOwner()-> GetActorForwardVector() * GrabDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	FHitResult HitResult;
	bool PickUpHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1);

	if (PickUpHitResult)
	{
		//APickUp* PickUp = Cast<APickUp>(HitResult.Actor); 
	}
}

