#include "ShadowGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, "InputTag.LMB");
UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, "InputTag.RMB");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Shift, "InputTag.Shift");
UE_DEFINE_GAMEPLAY_TAG(InputTag_Q, "InputTag.Q");
UE_DEFINE_GAMEPLAY_TAG(InputTag_E, "InputTag.E");
UE_DEFINE_GAMEPLAY_TAG(InputTag_R, "InputTag.R");

// 阵营识别
UE_DEFINE_GAMEPLAY_TAG(Faction_Player, "Faction.Player");
UE_DEFINE_GAMEPLAY_TAG(Faction_Enemy, "Faction.Enemy");

// 状态标签——状态锁
UE_DEFINE_GAMEPLAY_TAG(State_Locker_Attacking,"State.Locker.Attacking");
UE_DEFINE_GAMEPLAY_TAG(State_Locker_Sprinting,"State.Locker.Sprinting");

// 状态标签——Debuff
UE_DEFINE_GAMEPLAY_TAG(State_Debuff_Stunned,"State.Debuff.Stunned");

// 状态标签——状态
UE_DEFINE_GAMEPLAY_TAG(State_Status_Parry, "State.Status.Parry");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Dodge, "State.Status.Dodge");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Invincible, "State.Status.Invincible");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Dead, "State.Status.Dead");

UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Dao_MeleeAttack_X, "Ability.Weapon.Dao.MeleeAttack.X");
UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Dao_MeleeAttack_XX, "Ability.Weapon.Dao.MeleeAttack.XX");
UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Dao_MeleeAttack_XXX, "Ability.Weapon.Dao.MeleeAttack.XXX");

UE_DEFINE_GAMEPLAY_TAG(Effect_EnergyIncreased_Green, "Effect.EnergyIncreased.Green");
UE_DEFINE_GAMEPLAY_TAG(Effect_EnergyIncreased_Red, "Effect.EnergyIncreased.Red");
UE_DEFINE_GAMEPLAY_TAG(Effect_EnergyIncreased_White, "Effect.EnergyIncreased.White");
UE_DEFINE_GAMEPLAY_TAG(Combo_X, "Combo.X");
UE_DEFINE_GAMEPLAY_TAG(Combo_XX, "Combo.XX");
UE_DEFINE_GAMEPLAY_TAG(Combo_XXX, "Combo.XXX");
UE_DEFINE_GAMEPLAY_TAG(Attack_Damage_Start, "Attack.Damage.Start");
UE_DEFINE_GAMEPLAY_TAG(Attack_Damage_End, "Attack.Damage.End");

// 对抗
UE_DEFINE_GAMEPLAY_TAG(Battle_ByBlocked, "Battle.ByBlocked");
UE_DEFINE_GAMEPLAY_TAG(Battle_ParrySuccess, "Battle.ParrySuccess");
UE_DEFINE_GAMEPLAY_TAG(Battle_HitReact, "Battle.HitReact");
UE_DEFINE_GAMEPLAY_TAG(Battle_Attack, "Battle.Attack");	// 可被弹刀类型攻击