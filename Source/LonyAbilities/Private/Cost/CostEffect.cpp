// © Lony Studios / Matheus Vilano

#include "Cost/CostEffect.h"

UCostEffect::UCostEffect() : Super()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}

bool UCostEffect::AddModifier(const FGameplayAttribute& Attribute, const FScalableFloat& ScalableFloat)
{
	FGameplayModifierInfo CostModifier;
	CostModifier.Attribute = Attribute;
	CostModifier.ModifierOp = EGameplayModOp::Additive;
	CostModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(ScalableFloat);
	
	return Modifiers.AddUnique(CostModifier) < 0;  // If `Add` fails, it returns -1.
}
