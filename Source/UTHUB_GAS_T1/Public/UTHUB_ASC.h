// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UTHUB_ASC.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTHUB_GAS_T1_API UUTHUB_ASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UUTHUB_ASC();


protected:
	virtual  void BeginPlay() override;

public:
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
