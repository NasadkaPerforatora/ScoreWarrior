#ifndef __GAME_CORE_INPUT_PROCESSING_SCRIPT_PROCESSOR_H__
#define __GAME_CORE_INPUT_PROCESSING_SCRIPT_PROCESSOR_H__

#include "../error.h"
#include <memory>
#include <string>
#include <vector>

namespace game::core::input_processing
{

struct IScriptParcer
{
	virtual Error Parse(const std::string& filePath, std::vector<Command>& commands) = 0;
};

std::unique_ptr<IScriptParcer> CreateScriptParcer();

} // namespace game::core::input_processing

#endif // __GAME_CORE_INPUT_PROCESSING_SCRIPT_PROCESSOR_H__
