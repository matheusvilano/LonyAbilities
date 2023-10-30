// © Lony Studios / Matheus Vilano

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "CooldownCalculation.generated.h"

/**
 * A calculation class. Handles calculation of a UGameplayAbilityEnhanced's cooldown.
 * @note Using this as a modifier for an effect applied to an ability that does not inherit from `UGameplayAbilityEnhanced`
 * will result in a cooldown of 0.
 */
UCLASS()
class LONYABILITIES_API UCooldownCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	/**
	 * Calculates the cooldown duration of an ability.
	 * @param Spec The gameplay effect spec to calculate the cooldown for.
	 * @return The cooldown duration of this ability.
	 */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
