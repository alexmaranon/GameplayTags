// Fill out your copyright notice in the Description page of Project Settings.


#include "PokeAttack.h"

#include "Pokemon.h"

void UPokeAttack::Attack(APokemon* PokemonTarget)
{
	if(PokemonTarget && AttackAttribs->Uses >0)
	{

		PokemonTarget->ReceiveDamage(AttackAttribs->AttackType,AttackAttribs->Damage);

		AttackAttribs->Uses -= 1;


		UE_LOG(LogTemp, Log, TEXT("Uses = %f"), AttackAttribs->Uses);
	}
	

}

void UPokeAttack::InitializeAttack(FAttackAttributes* AttackData)
{
	AttackAttribs = AttackData;
}
