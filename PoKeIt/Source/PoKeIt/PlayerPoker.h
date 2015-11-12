// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameFramework/PlayerController.h"
#include "PlayerPoker.generated.h"





/**
 * 
 */
UCLASS()
class POKEIT_API APlayerPoker : public APlayerController
{
	GENERATED_BODY()
		
		//UFUNCTION(BlueprintCallable, Category = "chips")
		//void setChips();


		

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "damage")
		int32 chips;

	//UFUNCTION(BlueprintCallable, Category = "chips")
	void setChips();


	// Card hand[2];

	//UFUNCTION(BlueprintCallable, Category = "receivingCards")
	void receiveCards();

	//UFUNCTION(BlueprintCallable, Category = "callRound")
	void callRound();

	//UFUNCTION(BlueprintCallable, Category = "checkRound")
	void checkRound();

	//UFUNCTION(BlueprintCallable, Category = "raiseRound")
	void raiseRound();

	//UFUNCTION(BlueprintCallable, Category = "foldRound")
	void foldRound();


	
	
};
