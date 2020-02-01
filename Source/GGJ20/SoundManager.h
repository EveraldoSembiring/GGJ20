#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AK/SoundEngine/Common/AkTypes.h>
#include <AKAudio/Classes/AkGameplayTypes.h>
#include "SoundManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoundDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserCueSoundDelegate, FString, userCueName);

UCLASS()
class GGJ20_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void PlayBGM(class UAkAudioEvent* bgmEvent);

	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void StopBGM(class UAkAudioEvent* bgmEvent);

	UFUNCTION(BlueprintCallable, Category = "Sounds")
	void PlaySFX(class UAkAudioEvent* sfxEvent);

private:
	UFUNCTION()
	void OnBGMCallback(EAkCallbackType CallbackType, UAkCallbackInfo* CallbackInfo);

public:
	UPROPERTY(Category = "Component", EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintAssignable, Category = "Sounds|Events")
	FSoundDelegate OnBGMStart;

	UPROPERTY(BlueprintAssignable, Category = "Sounds|Events")
	FSoundDelegate OnBGMEnd;

	UPROPERTY(BlueprintAssignable, Category = "Sounds|Events")
	FSoundDelegate OnBGMBeat;

	UPROPERTY(BlueprintAssignable, Category = "Sounds|Events")
	FSoundDelegate OnBGMBar;

	UPROPERTY(BlueprintAssignable, Category = "Sounds|Events")
	FUserCueSoundDelegate OnBGMCue;

private:
	int32 BGMid;
	FOnAkPostEventCallback BGMCallback;

};
