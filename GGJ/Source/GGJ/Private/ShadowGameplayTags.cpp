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
UE_DEFINE_GAMEPLAY_TAG(State_Status_HitReact, "State.Status.HitReact");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Parry_Start, "State.Status.Parry.Start");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Parry_End, "State.Status.Parry.End");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Dodge_Start, "State.Status.Dodge.Start");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Dodge_End, "State.Status.Dodge.End");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Invincible, "State.Status.Invincible");
UE_DEFINE_GAMEPLAY_TAG(State_Status_Dead, "State.Status.Dead");

UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Dao_MeleeAttack_X, "Ability.Weapon.Dao.MeleeAttack.X");
UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Dao_MeleeAttack_XX, "Ability.Weapon.Dao.MeleeAttack.XX");
UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Dao_MeleeAttack_XXX, "Ability.Weapon.Dao.MeleeAttack.XXX");

UE_DEFINE_GAMEPLAY_TAG(Effect_EnergyIncreased_Green, "Effect.EnergyIncreased.Green");
UE_DEFINE_GAMEPLAY_TAG(Effect_EnergyIncreased_Red, "Effect.EnergyIncreased.Red");
UE_DEFINE_GAMEPLAY_TAG(Effect_EnergyIncreased_White, "Effect.EnergyIncreased.WhiteX");
UE_DEFINE_GAMEPLAY_TAG(Combo_X, "Combo.X");
UE_DEFINE_GAMEPLAY_TAG(Combo_XX, "Combo.XX");
UE_DEFINE_GAMEPLAY_TAG(Combo_XXX, "Combo.XXX");

// 对抗
UE_DEFINE_GAMEPLAY_TAG(Battle_ByBlocked, "Battle.ByBlocked");
UE_DEFINE_GAMEPLAY_TAG(Battle_Attack, "Battle.Attack1");	// 可被弹刀类型攻击