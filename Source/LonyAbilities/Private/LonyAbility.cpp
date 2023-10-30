// © Lony Studios / Matheus Vilano

#include "LonyAbility.h"
#include "AbilitySystemComponent.h"
#include "Cooldown/CooldownEffect.h"
#include "Cost/CostEffect.h"

ULonyAbility::ULonyAbility()
{
	CooldownGameplayEffectClass = UCooldownEffect::StaticClass();
	CostGameplayEffectClass = UCostEffect::StaticClass();
}

float ULonyAbility::GetCooldownValue(const float& Level) const
{
	return Level > 0 ? CooldownScalable.GetValueAtLevel(Level) : CooldownScalable.Value;
}

float ULonyAbility::GetCostValue(const FGameplayAttribute& Attribute, const float& Level) const
{
	return Level > 0 ? CostScalable[Attribute].GetValueAtLevel(Level) : CostScalable[Attribute].Value;
}

const FGameplayTagContainer* ULonyAbility::GetCooldownTags() const
{
	FGameplayTagContainer* const MutableTags = const_cast<FGameplayTagContainer*>(&CooldownTags);

	if (MutableTags != nullptr)
	{
		if (const FGameplayTagContainer* const ParentTags = Super::GetCooldownTags(); ParentTags != nullptr)
		{
			MutableTags->AppendTags(*ParentTags);
		}
		else return nullptr;
	}

	return MutableTags;
}

UGameplayEffect* ULonyAbility::GetCooldownGameplayEffect() const
{
	return Super::GetCooldownGameplayEffect();
}

UGameplayEffect* ULonyAbility::GetCostGameplayEffect() const
{
	if (!CostGameplayEffectClass->IsChildOf(UCostEffect::StaticClass())) return Super::GetCostGameplayEffect();

	// Create a dynamic instant Gameplay Effect based on `CostScalable`.
	UCostEffect* CostEffect = NewObject<UCostEffect>(GetTransientPackage(), FName(TEXT("CostEffect")));
	CostEffect->DurationPolicy = EGameplayEffectDurationType::Instant;

	for (auto [Attribute, ScalableFloat] : CostScalable) // We can't get by ref here because the function is const.
	{
		ScalableFloat.Value *= -1; // Looks funky, but is correct. TTuple and FScalableFloat both use "Value" as an id.
		CostEffect->AddModifier(Attribute, ScalableFloat);
	}

	return CostEffect;
}

void ULonyAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
								 const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo) const
{
	const UGameplayEffect* const CooldownEffect = GetCooldownGameplayEffect();
	if (!IsValid(CooldownEffect)) return;

	const FGameplayEffectSpecHandle CooldownSpecHandle = MakeOutgoingGameplayEffectSpec(
		CooldownEffect->GetClass(), GetAbilityLevel());
	CooldownSpecHandle.Data->DynamicGrantedTags.AppendTags(CooldownTags);

	(void)ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, CooldownSpecHandle); // Ret value ignored.
}

void ULonyAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo) const
{
	const UGameplayEffect* const CostEffect = GetCostGameplayEffect();
	if (!IsValid(CostEffect)) return;

	const FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(
		CostEffect->GetClass(), GetAbilityLevel());

	CostSpecHandle.Data->Initialize(CostEffect, CostSpecHandle.Data->GetContext()); // Keep context, update spec handle.

	(void)ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, CostSpecHandle); // Ret value ignored.
}
