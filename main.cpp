#include "core/coordinates.h"
#include "core/command.h"
#include "core/error.h"
#include "core/engine/command_executor.h"
#include "core/input_processing/script_parcer.h"
#include "core/unit/unit.h"
#include "core/unit/warrior.h"
#include "utils/contracts.h"
#include "utils/logger.h"
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    try
    {
        const auto parcer{ game::core::input_processing::CreateScriptParcer() };
        std::vector<game::core::Command> commands;
        CHECK(parcer->Parse(argv[0], commands));

        auto executor{ game::core::engine::CreateCommandExecutor() };
        LOG("GAME STARTED");
        for (size_t i{ 0 }; i < commands.size(); ++i)
        {
            CHECK(executor->Execute(commands[i]));
        }
        LOG("GAME FINISED");
        
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception\n";
    }

    return 0;
}
