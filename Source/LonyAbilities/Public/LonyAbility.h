// © Lony Studios / Matheus Vilano

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LonyAbility.generated.h"

/**
 * A child class of `UGameplayAbility`, but with better support for gameplay effects.
 * Mainly, this class provides support for modular cost and cooldown gameplay effects.
 */
UCLASS()
class LONYABILITIES_API ULonyAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	ULonyAbility();

	/** @return The cooldown duration of this ability. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Lony|Abilities")
	inline float GetCooldownValue(const float& Level) const;

	/** @return The cost of this ability. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Lony|Abilities")
	inline float GetCostValue(const FGameplayAttribute& Attribute, const float& Level) const;

	/** @return The cooldown tags of this ability. */
	virtual const FGameplayTagContainer* GetCooldownTags() const override;

	/**
	 * Gets the cooldown gameplay effect.
	 * @return The cooldown gameplay effect.
	 */
	virtual UGameplayEffect* GetCooldownGameplayEffect() const override;

	/**
	 * Gets the cost gameplay effect. This is created dynamically depending on the data inside `CostScalable`.
	 * @return The cost gameplay effect.
	 */
	virtual UGameplayEffect* GetCostGameplayEffect() const override;

	/**
	 * Applies the cooldown tags.
	 * @param Handle The gameplay ability spec handle.
	 * @param ActorInfo The ability's actor info.
	 * @param ActivationInfo The ability's activation info.
	 */
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo) const override;

	/**
	 * Applies the cost operations.
	 * @param Handle The gameplay ability spec handle.
	 * @param ActorInfo The ability's actor info.
	 * @param ActivationInfo The ability's activation info.
	 */
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
						   const FGameplayAbilityActivationInfo ActivationInfo) const override;

private:
	/** The cooldown duration of this ability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cooldowns", DisplayName="Cooldown Duration",
		meta=(AllowPrivateAccess="true"))
	FScalableFloat CooldownScalable;

	/** The cooldown tags of this ability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cooldowns", DisplayName="Cooldown Tags",
		meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer CooldownTags;

	/**
	 * The cost of this ability, per attribute.
	 * @note If a value is negative, the attribute value will increase. Example: increasing a "BurnoutPercentage" attribute.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Costs", DisplayName="Cost Per Attribute",
		meta=(AllowPrivateAccess="true"))
	TMap<FGameplayAttribute, FScalableFloat> CostScalable;
};
