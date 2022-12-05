#ifndef __GAME_CORE_ERROR_H__
#define __GAME_CORE_ERROR_H__

#include <stdint.h>
#include <string>

namespace game::core
{

enum class Error
{
    Ok,
    InvalidScript,
    OutOfBounds,
    UnitAlreadyExists,
    SpawnOnNotEmptyCell,
    NotExists,
    UnknownCommand,
};

inline std::string ErrorToString(Error error)
{
    switch (error)
    {
    case game::core::Error::Ok:
        return "Ok";
    case game::core::Error::InvalidScript:
        return "InvalidScript";
    case game::core::Error::OutOfBounds:
        return "OutOfBounds";
    case game::core::Error::UnitAlreadyExists:
        return "UnitAlreadyExists";
    case game::core::Error::SpawnOnNotEmptyCell:
        return "SpawnOnNotEmptyCell";
    case game::core::Error::NotExists:
        return "NotExists";
    case game::core::Error::UnknownCommand:
        return "UnknownCommand";
    default:
        return "Unknown error";
    }
}

} // namespace game::core

#endif // __GAME_CORE_ERROR_H__
