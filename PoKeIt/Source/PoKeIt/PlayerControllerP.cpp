// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "PlayerP.h"
#include "Card.h"
#include "MyPlayerP.h"


int amountOfPlayers;
// default = 5


// since UE 4.6, constructor is not needed anymore
APlayerControllerP::APlayerControllerP()
{
	chips = 1337;
}

void APlayerControllerP::spawnPlayers(int amountOfPlayersSelected)
{
	amountOfPlayers = amountOfPlayersSelected;

	for (int i = 0; i < amountOfPlayers; ++i)
	{
		MyPlayerP *spawnedPlayer = new MyPlayerP(10000);
		spawnedPlayer->setCards();
		players[i] = spawnedPlayer;
	}

	roundManager = new RoundManager(players);


	updateHUD();

	/*
	UWorld* const World = GetWorld();

	if (World)
	{

		FVector position = FVector(500, 100, 30);
		FRotator rotator(0, 0, 0);

		//APlayerP* spawnedPlayer1 = World->SpawnActor<APlayerP>(position, rotator);
		//spawnedPlayer1->increaseChips();
		//spawnedPlayer1->increaseChips();

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("player1s chips are: %i"), spawnedPlayer1->getChips()));

		//AActor* segment = GetWorld()->SpawnActor(RopeSegment->GeneratedClass, &actorLocation, &actorRotation, spawnParams);


		FVector position2 = FVector(300, 150, 30);
		FRotator rotator2(0, 0, 0);

		//APlayerP* spawnedPlayer2 = World->SpawnActor<APlayerP>(position2, rotator2);
		//spawnedPlayer2->increaseChips();

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("player2s chips are: %i"), spawnedPlayer2->getChips()));

		//betRaise(spawnedPlayer1, spawnedPlayer2);

		//players[0] = spawnedPlayer1;
		//players[1] = spawnedPlayer2;

		TArray< APlayerP* > myArray;

		myArray.Add(World->SpawnActor<APlayerP>(position, rotator));
		myArray.Add(World->SpawnActor<APlayerP>(position2, rotator2));

		myArray[0]->increaseChips();
		myArray[0]->increaseChips();
		myArray[1]->increaseChips();

		//int one = myArray[0]->getChips();
		//int two = myArray[0]->getChips();


		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("players[0] chips are: %i"), myArray[0]->getChips()));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("players[1] chips are: %i"), myArray[1]->getChips()));


		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("players[0] chips are: %i"), players[0]->getChips()));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("players[1] chips are: %i"), players[1]->getChips()));
	
	

	
		for (int i = 0; i < amountOfPlayers; ++i)
		{

			FVector position = FVector(500, 100, 30);
			FRotator rotator(0, 0, 0);

			APlayerP* spawnedPlayer = World->SpawnActor<APlayerP>(APlayerP::StaticClass(), position, rotator);

			//players[i] = spawnedPlayer;

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "for loop entered");

		}
		
	}
	*/
	
}

void APlayerControllerP::updateHUD()
{
	currentPlayersChips = players[currentPlayer]->getChips();
	potSize = roundManager->getPot();
	getCurrentPlayerCards();
}

void APlayerControllerP::finishTurn()
{
	currentPlayer = ++currentPlayer % amountOfPlayers;
	updateHUD();
}

void APlayerControllerP::getCurrentPlayerCards()
{

	currentPlayersHand[0] = players[currentPlayer]->getCard0();
	currentPlayersHand[1] = players[currentPlayer]->getCard1();

	cardColor0 = currentPlayersHand[0]->getColor();
	cardValue0 = currentPlayersHand[0]->getValue();
	cardColor1 = currentPlayersHand[1]->getColor();
	cardValue1 = currentPlayersHand[1]->getValue();
}


void APlayerControllerP::betRaise(int atb)
{
	int amountToBet = atb;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("APC betRaise was called with: %i"), amountToBet));

}

void APlayerControllerP::foldRound()
{
	finishTurn();
}

void APlayerControllerP::receiveCards()
{

}

void APlayerControllerP::callRound()
{

}

void APlayerControllerP::checkRound()
{
	roundManager->checkRound();

}



