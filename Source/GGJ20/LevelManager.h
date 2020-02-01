#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AK/SoundEngine/Common/AkTypes.h>
#include "SoundManager.h"
#include "UObject/WeakObjectPtr.h"
#include "LevelManager.generated.h"

USTRUCT(BlueprintType)
struct FLevelPhase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Phase")
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Phase")
	int32 ChangeColorPerBeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level|Phase")
	TArray<FColor> AvailableColors;
	
	FLevelPhase()
	{
		ID = TEXT("");
		ChangeColorPerBeat = 4;
		AvailableColors.Init(FColor(1, 1, 1, 1), 1);
	}
};

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	class UAkAudioEvent* BGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FLevelPhase> Phases;

	FLevelData()
	{
		ID = TEXT("");
		BGM = NULL;
		Phases.Init(FLevelPhase(), 1);
	}
};

DECLARE_DYNAMIC_DELEGATE(FLevelDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLevelPhaseDelegate, FString, userPhaseID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerChangeColorDelegate, FColor, newPlayerColor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerChangePhaseDelegate, FLevelPhase, newPhase);

UCLASS()
class GGJ20_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckAndStartColorChange();

	UFUNCTION()
	void CheckAndStartPhaseChange(FString phaseID);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Level")
	bool StartLevel(FString levelID);

private:

	UPROPERTY()
	FLevelDelegate OnBGMBeat;

	UPROPERTY()
	FLevelPhaseDelegate OnBGMCue;

	UPROPERTY()
	bool IsStarted;

	UPROPERTY()
	FLevelData CurrentLevel;

	UPROPERTY()
	bool HaveLevelPhase;

	UPROPERTY()
	FLevelPhase CurrentLevelPhase;

	UPROPERTY()
	int32 CurrentBeat;

	UPROPERTY()
	int32 CurrentColorIndex;

public:
	UPROPERTY(Category = "Component", EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	class ASoundManager* Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FLevelData> Levels;

	UPROPERTY(BlueprintAssignable, Category = "Level")
	FPlayerChangeColorDelegate OnPlayerChangeColor;

	UPROPERTY(BlueprintAssignable, Category = "Level")
	FPlayerChangePhaseDelegate OnPlayerChangePhase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float CurrentTime;
};
