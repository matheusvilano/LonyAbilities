// © Lony Studios / Matheus Vilano

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "CooldownEffect.generated.h"

/** A cooldown effect. This works with `UCooldownCalculation` to calculate the cooldown duration. */
UCLASS()
class LONYABILITIES_API UCooldownEffect : public UGameplayEffect
{
	GENERATED_BODY()

	friend class ULonyAbility;
	
public:

	/** The default constructor. */
	UCooldownEffect();
};
