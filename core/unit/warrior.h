#ifndef __GAME_CORE_UNIT_WARRIOR_H__
#define __GAME_CORE_UNIT_WARRIOR_H__

#include "unit.h"
#include <memory>

namespace game::core::unit
{

struct WarriorSettings
{
	const size_t id{ 0 };
	const size_t force{ 0 };
	const core::Point coordinates;
};

std::shared_ptr<IUnit> CreateWarrior(const WarriorSettings& settings);

} // namespace game::core::unit

#endif // __GAME_CORE_UNIT_WARRIOR_H__
