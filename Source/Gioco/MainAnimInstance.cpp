// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay_Character/MyCharacter.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
  if (Pawn == nullptr) // controlla quale pawn è in controllo delle animazioni
 {
	  Pawn = TryGetPawnOwner();
	  if (Pawn)
{
		  Character = Cast<AMyCharacter>(Pawn);
		  Character->SetMainAnimInstance(this);
}
 }
  
}
void UMainAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size(); // per andare in diagonale quando spingi due tasti come "w" e "d"

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		if (Character == nullptr)
		{
			Character = Cast<AMyCharacter>(Pawn);
		}
	}
}
