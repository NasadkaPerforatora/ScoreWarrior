#ifndef __GAME_CORE_COMMAND_H__
#define __GAME_CORE_COMMAND_H__

#include <map>
#include <string>
#include <vector>

namespace game::core
{

constexpr auto CreateMapCommandName{ "CREATE_MAP" };
constexpr auto SpawnCommandName{ "SPAWN" };
constexpr auto MarchCommandName{ "MARCH" };
constexpr auto WaitCommandName{ "WAIT" };
constexpr auto FinishCommandName{ "FINISH"};

constexpr size_t CreateMapArgCount{ 2 };
constexpr size_t SpawnArgCount{ 4 };
constexpr size_t MarchArgCount{ 3 };
constexpr size_t WaitArgCount{ 1 };

static std::map<std::string, size_t> CommandsArgs = {
	{ CreateMapCommandName, CreateMapArgCount },
	{ SpawnCommandName, SpawnArgCount },
	{ MarchCommandName, MarchArgCount },
	{ WaitCommandName, WaitArgCount },
};

struct Command
{
	std::string name;
	std::vector<std::string> args;
};

} // namespace game::core

#endif // __GAME_CORE_ERROR_H__
