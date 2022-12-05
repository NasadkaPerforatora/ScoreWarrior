#ifndef __GAME_CORE_ENGINE_COMMAND_EXECUTOR_H__
#define __GAME_CORE_ENGINE_COMMAND_EXECUTOR_H__

#include "../command.h"
#include "../error.h"
#include <memory>

namespace game::core::engine
{

struct ICommandExecutor
{
	virtual Error Execute(const Command& command) = 0;
};

std::unique_ptr<ICommandExecutor> CreateCommandExecutor();

} // namespace game::core::engine

#endif // __GAME_CORE_ENGINE_COMMAND_EXECUTOR_H__
