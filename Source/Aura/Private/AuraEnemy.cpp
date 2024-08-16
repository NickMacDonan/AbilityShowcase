// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	bShouldHighlight = true;
}

void AAuraEnemy::UnHighlightActor()
{
	bShouldHighlight = false;
}
