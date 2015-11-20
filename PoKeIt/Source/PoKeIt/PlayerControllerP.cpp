// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "PlayerP.h"
#include "Card.h"



/*
Card* PlayerControllerP::getHand()
{
return hand*;
}
*/

// since UE 4.6, constructor is not needed anymore
APlayerControllerP::APlayerControllerP()
{
	chips = 1337;
	//APoKeItGameMode * p = new APoKeItGameMode();
}

void APlayerControllerP::increaseChips()
{

	chips += 1000;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "int chips was increased by 1000");

}


void APlayerControllerP::spawnPlayers(int numberOfPlayers)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "spawnPlayers was called");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("playernumber is: %i"), numberOfPlayers));

	UWorld* const World = GetWorld();
	
	if (World)
	{
		//APlayerP* SpawnedPlayer = GWorld()->SpawnActor(APlayerP::StaticClass());

		for (int i = 0; i < numberOfPlayers; ++i)
		{
			FVector position = FVector(500, 100, 30);
			FRotator rotator(0, 0, 0);

			APlayerP* spawnedPlayer = World->SpawnActor<APlayerP>(APlayerP::StaticClass(), position, rotator);

			players[i] = spawnedPlayer;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "for loop entered");
		}
	}	
	
}

void APlayerControllerP::foldRound()
{
	/*
	for (APlayerP * P : players)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "player P found");
	}
	*/

	
	for (int i = 0; i < 8; ++i)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%i"), i));
		players[i]->debugFunc();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("playernumber is: %i"), playersI));
	
}


void APlayerControllerP::receiveCards()
{

}

void APlayerControllerP::callRound()
{

}

void APlayerControllerP::checkRound()
{

}

void APlayerControllerP::raiseRound()
{

}

