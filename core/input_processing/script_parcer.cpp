#include "../../utils/contracts.h"
#include "../../utils/logger.h"
#include "../command.h"
#include "script_parcer.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace game::core::input_processing
{

class ScriptProcessor : public IScriptParcer
{
public:
	virtual ~ScriptProcessor() = default;

	Error Parse(const std::string& filePath, std::vector<Command>& commands) final
	{
        try
        {
            commands.clear();

            size_t createMapCommandCount{ 0 };

            std::ifstream stream(filePath);
            std::string command;
            while (std::getline(stream, command))
            {
                Command res{ ProcessCommand(command) };
                if (res.name == CreateMapCommandName)
                    ++createMapCommandCount;
                if (createMapCommandCount > 1)
                    return Error::InvalidScript;
                
                commands.push_back(std::move(res));
            }
            commands.push_back(Command{ FinishCommandName, {} });
        }
        catch (const std::exception& ex)
        {
            LOG(ex.what());
            return Error::InvalidScript;
        }
        catch (...)
        {
            return Error::InvalidScript;
        }

        return Error::Ok;
	}

private:
    Command ProcessCommand(const std::string& command)
    {
        std::stringstream ss(command);
        std::string commandName;
        ss >> commandName;
        EXPECT_FALSE(commandName.empty());

        Command result;
        const auto processArgs = [&](const size_t argCount) {
            std::string arg;
            for (size_t i{ 0 }; i < argCount; ++i)
            {
                ss >> arg;
                EXPECT_FALSE(arg.empty());
                result.args.push_back(arg);
            }
        };

        const auto it{ CommandsArgs.find(commandName) };
        std::cout << "Current Command Name: " << commandName << std::endl;
        EXPECT_FALSE(it == CommandsArgs.end());

        result.name = commandName;
        processArgs(it->second);

        return result;
    }
};

std::unique_ptr<IScriptParcer> CreateScriptParcer()
{
    return std::make_unique<ScriptProcessor>();
}

} // namespace game::core::input_processing
