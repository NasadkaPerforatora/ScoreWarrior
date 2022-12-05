#ifndef __GAME_CORE_COORDINATES_H__
#define __GAME_CORE_COORDINATES_H__

#include <stdint.h>

namespace game::core
{

struct Point
{
	int64_t x{ 0 };
	int64_t y{ 0 };
};

} // namespace game::core

#endif // __GAME_CORE_COORDINATES_H__
