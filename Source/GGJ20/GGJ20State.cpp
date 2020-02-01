// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ20State.h"

bool AGGJ20State::LoseHealth()
{
	return true;
}

void AGGJ20State::AbsorbHealth()
{
	_health = _health + 1;
}
