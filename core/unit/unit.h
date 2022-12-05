#ifndef __GAME_CORE_UNIT_UNIT_H__
#define __GAME_CORE_UNIT_UNIT_H__

#include "../coordinates.h"
#include <stddef.h>

namespace game::core::unit
{

struct IUnit
{
    virtual size_t GetId() const = 0;
    virtual size_t GetForce() const = 0;
    virtual Point GetCoordinates() const = 0;
    virtual void SetCoordinates(const Point coordinates) = 0;
};

} // namespace game::core::unit

#endif // __GAME_CORE_UNIT_UNIT_H__
