#ifndef __GAME_UTILS_CONTRACTS_H__
#define __GAME_UTILS_CONTRACTS_H__

#include "../core/error.h"
#include <sstream>
#include <exception>

#define EXPECT_FALSE(expr) \
    if (expr) { \
        std::stringstream ss; \
        ss << "Contract violation: EXPECT FALSE at file: " << __FILE__ << " line: " << __LINE__; \
        throw std::runtime_error(ss.str()); \
    }

#define EXPECT_NOT_NULL(expr) \
    if (expr == nullptr) { \
        std::stringstream ss; \
        ss << "Contract violation: EXPECT NOT NULL at file: " << __FILE__ << " line: " << __LINE__; \
        throw std::runtime_error(ss.str()); \
    }

#define CHECK(error) \
    if (error != game::core::Error::Ok) { \
        std::stringstream ss; \
        ss << "Error code == " << game::core::ErrorToString(error) << " at file: " << __FILE__ << " line: " << __LINE__; \
        throw std::runtime_error(ss.str()); \
    }

#endif // __GAME_UTILS_CONTRACTS_H__
