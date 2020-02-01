#include "LevelManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALevelManager::ALevelManager()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetVisibility(false, false);
	SetRootComponent(Mesh);

	Levels.Init(FLevelData(), 1);
	OnBGMBeat.BindUFunction(this, "CheckAndStartColorChange");
	OnBGMCue.BindUFunction(this, "CheckAndStartPhaseChange");

	IsStarted = false;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (Sounds != NULL)
	{
		Sounds->OnBGMBeat.Add(OnBGMBeat);
		Sounds->OnBGMCue.Add(OnBGMCue);
	}
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsStarted)
	{
		CurrentTime += DeltaTime;
	}
}

void ALevelManager::CheckAndStartColorChange()
{
	if (!HaveLevelPhase)
	{
		return;
	}

	CurrentBeat++;
	if (CurrentBeat >= CurrentLevelPhase.ChangeColorPerBeat)
	{
		// Change color now
		CurrentColorIndex++;
		if (CurrentColorIndex >= CurrentLevelPhase.AvailableColors.Num())
		{
			CurrentColorIndex = 0;
		}

		OnPlayerChangeColor.Broadcast(CurrentLevelPhase.AvailableColors[CurrentColorIndex]);

		// Wait for the next color change
		CurrentBeat = 0;
	}
}

void ALevelManager::CheckAndStartPhaseChange(FString phaseID)
{
	for (int i = 0; i < CurrentLevel.Phases.Num(); i++)
	{
		FLevelPhase levelPhase = CurrentLevel.Phases[i];
		if (levelPhase.ID.Equals(phaseID))
		{
			CurrentLevelPhase = levelPhase;
			HaveLevelPhase = true;
			CurrentBeat = 0;
			CurrentColorIndex = 0;
		}
	}
}

bool ALevelManager::StartLevel(FString levelID)
{
	int levelLength = Levels.Num();
	for (int i = 0; i < levelLength; i++)
	{
		FLevelData level = Levels[i];
		if (level.ID.Equals(levelID))
		{
			IsStarted = true;
			CurrentLevel = level;
			CurrentBeat = 0;
			CurrentColorIndex = 0;
			CurrentTime = 0;
			HaveLevelPhase = false;

			if (Sounds != NULL)
			{
				Sounds->PlayBGM(CurrentLevel.BGM);
			}

			return true;
		}
	}

	return false;
}

