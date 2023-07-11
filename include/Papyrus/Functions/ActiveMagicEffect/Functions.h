#pragma once

namespace Papyrus::ActiveMagicEffect::Functions
{
	inline RE::TESForm* GetActiveEffectSpell(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::ActiveEffect* a_activeEffect)
	{
		if (!a_activeEffect) {
			a_vm->TraceStack("Active Effect is None", a_stackID);
			return nullptr;
		}

		return a_activeEffect->spell;
	}

	inline bool IsScriptAttachedToActiveEffect(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::ActiveEffect* a_activeEffect,
		RE::BSFixedString       a_scriptName)
	{
		if (!a_activeEffect) {
			a_vm->TraceStack("Active Effect is None", a_stackID);
			return false;
		}

		return SCRIPT::is_script_attached(a_activeEffect, a_scriptName);
	}

	inline void Bind(VM& a_vm)
	{
		BIND(GetActiveEffectSpell);
		BIND(IsScriptAttachedToActiveEffect);

		logger::info("Registered activemagiceffect functions"sv);
	}
}
