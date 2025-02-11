// Fill out your copyright notice in the Description page of Project Settings.


#include "Pokemon.h"

#include <string>

void APokemon::InitializePokemon()
{
	if (PokemonData)
	{
		TArray<FPokemonAttributes*> OutData;
		PokemonData->GetAllRows(TEXT(""), OutData);

		if (!OutData.IsEmpty())
		{
			FPokemonAttributes** Attr = OutData.FindByPredicate([this](FPokemonAttributes* Row)
				{
					//Match the Pokemon selected tag with the datatable pokemon tag
					return Row->Pokemon.MatchesTag(Pokemon);
				});
			if (Attr) PokeAttributes = *Attr;

			if(AttackDataTable)

				for (const FName& AttackName : PokeAttributes->AttackNames)
				{
					//Create Attack comparing the String with the datatable row name 
					FAttackAttributes* AttackData = AttackDataTable->FindRow<FAttackAttributes>(AttackName, TEXT(""));
					if(AttackData)
					{
						
						UPokeAttack* NewAttack = NewObject<UPokeAttack>(this, UPokeAttack::StaticClass());
						NewAttack->InitializeAttack(AttackData);
						//Max 4 attacks
						if(Attacks.Num()<4){ Attacks.Add(NewAttack); }
						
					}
				}
		}
	}
}

APokemon::APokemon()
{
	ASC = CreateDefaultSubobject<UUTHUB_ASC>(TEXT("ASC"));
	PrimaryActorTick.bCanEverTick = true;

}

class UAbilitySystemComponent* APokemon::GetAbilitySystemComponent() const
{
	return ASC;
}

void APokemon::BeginPlay()
{
	Super::BeginPlay();

	InitializePokemon();

	//Test First attack with delay so all characters are initialized
		GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this]()
	{
		if (Attacks.Num() > 0 && Attacks[0] && PokemonTarget)
		{
			UE_LOG(LogTemp, Log, TEXT("%s : Attack: %s"), *PokeAttributes->Pokemon.ToString(), *PokeAttributes->AttackNames[0].ToString());
			Attacks[0]->Attack(PokemonTarget);
		}
	}, 2.0f, false);
}

// Called every frame
void APokemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float APokemon::GetEffectiveness(FGameplayTag AttackType) const
{

	if (TypeEffectivenessTable)
	{
		TArray<FPokemonTypeEffectiveness*> OutData;
		TypeEffectivenessTable->GetAllRows(TEXT(""), OutData);

		if (!OutData.IsEmpty())
		{
			FPokemonTypeEffectiveness** Attr = OutData.FindByPredicate([this, AttackType](FPokemonTypeEffectiveness* Row)
				{
					//We get the elementtype of the datatable depending on this pokemon type
					return Row->ElementType.MatchesTag(PokemonType);
				});

			if (Attr)
			{
				//We get the Substruct of the previous struct
				FElementsEffectiveness* EffectivenessData = (*Attr)->ElementsEffectivenessesList.FindByPredicate([AttackType](const FElementsEffectiveness& Effectiveness)
				{
						//On the Datatable we search the Element related to the income AttackType
						
						return Effectiveness.IncomeElementType.MatchesTag(AttackType);
						
				});
				//If it exists we get the effectiveness rate of the income attack
				if (EffectivenessData) return EffectivenessData->Effectiveness ;

				
			}
		}
		
	}
	 return 1.0f;

}
//Called by the PokeAttack which gives its attacktype and attack damage
void APokemon::ReceiveDamage(FGameplayTag AttackType, float Damage) const
{
	
	if(PokeAttributes)
	{
		//We give the attacktype of the income attack to the effectiveness
		float damage = Damage * GetEffectiveness(AttackType);
		PokeAttributes->Health -= damage;


		UE_LOG(LogTemp, Log, TEXT("HP: %f"), PokeAttributes->Health);
	}
	
}

// Called to bind functionality to input
void APokemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

