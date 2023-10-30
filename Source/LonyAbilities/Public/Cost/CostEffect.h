// © Lony Studios / Matheus Vilano

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "CostEffect.generated.h"

/** A cooldown effect. This works with `UCooldownCalculation` to calculate the cooldown duration. */
UCLASS()
class LONYABILITIES_API UCostEffect : public UGameplayEffect
{
	GENERATED_BODY()

	friend class ULonyAbility;
	
public:

	/** The default constructor. */
	UCostEffect();

protected:
	/**
	 * Adds a cost modifier to this effect. Example: calling this with a "Health" attribute will set it to be modified.
	 * @param Attribute The attribute to modify (add to or remove from).
	 * @param ScalableFloat The scalable float used to define the ability's cost.
	 * @return Whether this operation worked.
	 * @note This function will fail if the Attribute is already being modified by this effect.
	 */
	virtual bool AddModifier(const FGameplayAttribute& Attribute, const FScalableFloat& ScalableFloat);
};
