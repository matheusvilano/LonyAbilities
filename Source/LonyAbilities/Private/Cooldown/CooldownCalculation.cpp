// © Lony Studios / Matheus Vilano

#include "Cooldown/CooldownCalculation.h"
#include "LonyAbility.h"

float UCooldownCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const ULonyAbility* const Ability = Cast<ULonyAbility>(
		Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!IsValid(Ability)) return Super::CalculateBaseMagnitude_Implementation(Spec); // 0.f, by default.

	return Ability->GetCooldownValue(Ability->GetAbilityLevel());
}
