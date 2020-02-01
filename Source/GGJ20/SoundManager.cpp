#include "SoundManager.h"
#include <AkAudio\Classes\AkGameplayStatics.h>

// Sets default values
ASoundManager::ASoundManager()
{
	PrimaryActorTick.bCanEverTick = false;
	BGMCallback.BindUFunction(this, "OnBGMCallback");
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void ASoundManager::PlayBGM(class UAkAudioEvent* bgmEvent)
{
	BGMid = UAkGameplayStatics::PostEvent(	bgmEvent, this, 
											AkCallbackType::AK_MusicSyncBar | AkCallbackType::AK_MusicSyncBeat | AkCallbackType::AK_MusicSyncEntry | AkCallbackType::AK_MusicSyncExit | AkCallbackType::AK_MusicSyncUserCue, 
											BGMCallback);
}

void ASoundManager::StopBGM(class UAkAudioEvent* bgmEvent)
{
	UAkGameplayStatics::ExecuteActionOnPlayingID(AkActionOnEventType::Stop, BGMid, 500);
}

void ASoundManager::PlaySFX(class UAkAudioEvent* sfxEvent)
{
	FOnAkPostEventCallback nullCallback;
	UAkGameplayStatics::PostEvent(sfxEvent, this, int32(0), nullCallback);
}

void ASoundManager::OnBGMCallback(EAkCallbackType CallbackType, UAkCallbackInfo* CallbackInfo)
{
	switch (CallbackType)
	{
	case EAkCallbackType::MusicSyncBar:
		OnBGMBar.Broadcast();
		break;
	case EAkCallbackType::MusicSyncBeat:
		OnBGMBeat.Broadcast();
		break;
	case EAkCallbackType::MusicSyncEntry:
		OnBGMStart.Broadcast();
		break;
	case EAkCallbackType::MusicSyncExit:
		OnBGMEnd.Broadcast();
		break;
	case EAkCallbackType::MusicSyncUserCue:
		{
			UAkMusicSyncCallbackInfo* syncCallbackInfo = (UAkMusicSyncCallbackInfo*)CallbackInfo;
			OnBGMCue.Broadcast(syncCallbackInfo->UserCueName);
		}
		break;
	default:
		break;
	}
}
