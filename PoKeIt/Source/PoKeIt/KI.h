// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyPlayerP.h"

/**
 * 
 */
class POKEIT_API KI : public MyPlayerP
{
public:
	KI(int givenChips, FString nameGiven);
	~KI();
};
