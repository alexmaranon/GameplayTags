// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UTHUB_ASC.h"
#include "PokeAttack.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Pokemon.generated.h"


USTRUCT(BlueprintType)
struct FElementsEffectiveness : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag IncomeElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Effectiveness;
};


USTRUCT(BlueprintType)
struct FPokemonTypeEffectiveness : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FElementsEffectiveness> ElementsEffectivenessesList;

};


USTRUCT()
struct FPokemonAttributes : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) FGameplayTag Pokemon;

	UPROPERTY(EditAnywhere)	FGameplayTag PokemonType;
	UPROPERTY(EditAnywhere)	float Health;
	//UPROPERTY(EditAnywhere)	TArray<TSubclassOf<UPokeAttack>> Attacks;
	UPROPERTY(EditAnywhere) TArray<FName> AttackNames;

};

UCLASS()
class UTHUB_GAS_T1_API APokemon : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()



private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FGameplayTag Pokemon;

	FPokemonAttributes* PokeAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FGameplayTag PokemonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UDataTable* PokemonData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UDataTable* TypeEffectivenessTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	APokemon* PokemonTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UDataTable* AttackDataTable;
	UPROPERTY()
	TArray<UPokeAttack*> Attacks;



	void InitializePokemon();

public:
	// Sets default values for this character's properties
	APokemon();
	FORCEINLINE virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetEffectiveness(FGameplayTag AttackType) const ;

	void ReceiveDamage(FGameplayTag AttackType, float Damage) const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTimerHandle AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UUTHUB_ASC* ASC;
};
