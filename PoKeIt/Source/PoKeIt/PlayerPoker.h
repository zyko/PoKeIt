// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class POKEIT_API PlayerPoker
{
public:
	//int chips;

	PlayerPoker();
	~PlayerPoker();

	void receiveCard();
	void callRound();
	void checkRound();
	void raiseRound();
	void foldRound();
};
