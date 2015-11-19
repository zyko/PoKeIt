// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerP.h"


// Sets default values
APlayerP::APlayerP()
{



	/*
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	*/
}


void APlayerP::debugFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "PlayerP's debug Func was called");
}


/*
// Called when the game starts or when spawned
void APlayerP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

*/