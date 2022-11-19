// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "AIController.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (Actor_1 && Actor_2 && Actor_3 && Actor_4 && Actor_5 && Actor_6 && Actor_7)
	{
		SpawnArray.Add(Actor_1);
		SpawnArray.Add(Actor_2);
		SpawnArray.Add(Actor_3);
		SpawnArray.Add(Actor_4);
		SpawnArray.Add(Actor_5);
		SpawnArray.Add(Actor_6);
		SpawnArray.Add(Actor_7);
	}
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnVolume::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent(); //restituirà l'estensione della nostra scatola e possiamo archiviarla nel nostro vettore.
	FVector Origin = SpawningBox->GetComponentLocation(); // ci restituisce la locazione di origine del box
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

	return Point;
}

void ASpawnVolume::SpawnOurActor_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if (ToSpawn)
	{
		UWorld* World = GetWorld(); // UWorld è un object che gestisce gli actor, pawn e character
		FActorSpawnParameters SpawnParams;
		if (World)
		{
			AActor* Actor = World->SpawnActor<AActor>(ToSpawn, Location, FRotator(0.f), SpawnParams);
			
			AEnemy* Enemy = Cast<AEnemy>(Actor);
			if (Enemy)
			{
				Enemy->SpawnDefaultController();

				AAIController* AICont = Cast<AAIController>(Enemy->GetController());
				if (AICont)
				{
					Enemy->AIController = AICont;
				}
			}
		}
	}
}

TSubclassOf<AActor> ASpawnVolume::GetSpawnActor()
{
	if (SpawnArray.Num() > 0)
	{
		int32 Selection = FMath::RandRange(0, SpawnArray.Num() - 1);
		return SpawnArray[Selection];
	}
	else
	{
		return nullptr;
	}
}