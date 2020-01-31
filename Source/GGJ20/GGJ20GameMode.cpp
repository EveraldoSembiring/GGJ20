// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GGJ20GameMode.h"
#include "GGJ20Pawn.h"

AGGJ20GameMode::AGGJ20GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AGGJ20Pawn::StaticClass();
}

