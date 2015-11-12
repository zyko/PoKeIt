// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PlayerPoker.generated.h"

/**
 * 
 */
UCLASS()
class POKEIT_API APlayerPoker : public APlayerController
{
	GENERATED_BODY()

private:
	// Card hand[2];
	int chips;

	void receiveCards();
	void callRound();
	void checkRound();
	void raiseRound();
	void foldRound();

	
	
	
	
};
