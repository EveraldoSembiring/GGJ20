// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GGJ20State.generated.h"

/**
 * 
 */
UCLASS()
class GGJ20_API AGGJ20State : public AGameStateBase
{
	GENERATED_BODY()

public:
	void AbsorbHealth();
	bool LoseHealth();

private:

	UPROPERTY(Category = "Data", EditAnywhere)
	int32 _health;
};
