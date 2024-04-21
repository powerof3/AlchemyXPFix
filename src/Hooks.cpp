#include "Hooks.h"

namespace AlchemyXP
{
	struct AddIngredientUse
	{
		static void thunk(RE::IngredientItem* a_this, std::int32_t a_alchemyUses)
		{
		    func(a_this, a_alchemyUses);

			RE::MagicItem::SkillUsageData data{};
		    if (a_this->GetSkillUsageData(data)) {
				RE::PlayerCharacter::GetSingleton()->UseSkill(data.skill, data.magnitude, nullptr);
				
				if (auto craftingMenu = RE::UI::GetSingleton()->GetMenu<RE::CraftingMenu>()) {
					if (craftingMenu->subMenu) {
						craftingMenu->subMenu->UpdateCraftingInfo(RE::ActorValue::kAlchemy);
					}
				}
			}
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};

	void Install()
	{
		REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(50449, 51354), OFFSET(0x5A7, 0x5C7) };
		stl::write_thunk_call<AddIngredientUse>(target.address());
	}
}
