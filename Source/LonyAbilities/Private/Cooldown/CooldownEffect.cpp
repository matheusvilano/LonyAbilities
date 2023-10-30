// © Lony Studios / Matheus Vilano

#include "Cooldown/CooldownEffect.h"
#include "Cooldown/CooldownCalculation.h"

UCooldownEffect::UCooldownEffect() : Super()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	
	FCustomCalculationBasedFloat CustomCalculation;
	CustomCalculation.CalculationClassMagnitude = UCooldownCalculation::StaticClass();
	CustomCalculation.Coefficient = 1.f;
	
	DurationMagnitude = FGameplayEffectModifierMagnitude(CustomCalculation);
}
