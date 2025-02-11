// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UTHUB_ASC.h"
#include "UObject/NoExportTypes.h"
#include "PokeAttack.generated.h"

class APokemon;

USTRUCT()
struct FAttackAttributes : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)	FGameplayTag AttackType;
	UPROPERTY(EditAnywhere)	float Damage;
	UPROPERTY(EditAnywhere) float Uses;
};


UCLASS()
class UTHUB_GAS_T1_API UPokeAttack : public UObject
{
	GENERATED_BODY()

	FAttackAttributes* AttackAttribs;

public:

	virtual void Attack(APokemon* PokemonTarget);

	void InitializeAttack(FAttackAttributes* AttackData);

private:
	int AttacksLeft;

};
