#include "command_executor.h"
#include "../coordinates.h"
#include "../../utils/logger.h"
#include "../unit/warrior.h"
#include <cmath>
#include <list>

namespace game::core::engine
{
namespace {

class GameField
{
private:
    using UnitId = size_t;

    struct Cell
    {
        bool isEmpty{ true };
        std::weak_ptr<core::unit::IUnit> unit;
    };

    struct Task
    {
        size_t ticks{ 1 };
        std::weak_ptr<core::unit::IUnit> unit;
        core::Point destCoordinates;
    };

public:
    void ResetGameField(const Point boundary) noexcept
    {
        m_tasks.clear();
        m_field.clear();
        m_boundary = boundary;

        m_field.resize(m_boundary.x);
        for (auto& row : m_field)
        {
            row.resize(m_boundary.y);
        }

        LOG("[" << ++CurrentTick << "]" << "MAP CREATED " << m_boundary.y << " " << m_boundary.x);
    }

    core::Error AddUnit(const size_t uintId, const size_t force, const core::Point coordinates) noexcept
    {
        if (coordinates.x > m_boundary.x || coordinates.y > m_boundary.y)
            return core::Error::OutOfBounds;

        auto& cell{ m_field[coordinates.x][coordinates.y] };
        if (!cell.isEmpty)
            return core::Error::SpawnOnNotEmptyCell;

        std::map<size_t, std::shared_ptr<core::unit::IUnit>>::iterator it;
        bool isInserted{ false };
        std::tie(it, isInserted) = m_units.emplace(uintId, core::unit::CreateWarrior(core::unit::WarriorSettings{ uintId, force, coordinates }));

        if (!isInserted)
            return core::Error::UnitAlreadyExists;

        cell.isEmpty = false;
        cell.unit = it->second;

        LOG("[" << ++CurrentTick << "]" << "WARRIOR SPAWNED " << uintId << " ON " << coordinates.x << " " << coordinates.y);

        return core::Error::Ok;
    }

    core::Error AddTask(const size_t uintId, const core::Point coordinates) noexcept
    {
        if (coordinates.x > m_boundary.x || coordinates.y > m_boundary.y)
            return core::Error::OutOfBounds;

        const auto it{ m_units.find(uintId) };
        if (it == m_units.end())
            return core::Error::NotExists;

        auto war{ it->second };
        size_t ticks{
            static_cast<size_t>(std::sqrt(std::pow(coordinates.x - war->GetCoordinates().x, 2) + std::pow(coordinates.y - war->GetCoordinates().y, 2))) };
        if (ticks == 0)
            return core::Error::Ok;

        m_tasks.push_back({ ticks, war, coordinates });

        LOG("[" << ++CurrentTick << "]" << "MARCH STARTED " << uintId << " TO " << coordinates.x << " " << coordinates.y);

        return core::Error::Ok;
    }

    void DoOneTickForAllTasks() noexcept
    {
        for (auto it{ m_tasks.begin() }; it != m_tasks.end();)
        {
            if (bool isComplete{ Tick(*it, ++CurrentTick) }; isComplete)
            {
                it = m_tasks.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void DoTicksForAllTasks(size_t ticks) noexcept
    {
        for (; ticks > 0; --ticks)
        {
            DoOneTickForAllTasks();
        }
    }

    void CompleteAllTasks() noexcept
    {
        while (!m_tasks.empty())
        {
            DoOneTickForAllTasks();
        }
    }

private:
    bool Tick(Task& task, size_t currentTick) noexcept
    {
        if (--(task.ticks) == 0)
        {
            auto& cell{ m_field[task.destCoordinates.x][task.destCoordinates.y] };
            if (!cell.isEmpty)
            {
                if (auto enemy{ cell.unit.lock() })
                {
                    auto unit{ task.unit.lock() };
                    if (unit->GetForce() > enemy->GetForce())
                    {
                        m_units.erase(enemy->GetId());

                        unit->SetCoordinates(task.destCoordinates);
                        cell.unit = unit;
                        cell.isEmpty = false;

                        LOG("[" << currentTick << "]" << "MARCH " << unit->GetId() << " FINISHED " << unit->GetCoordinates().x << " "
                            << unit->GetCoordinates().y << " BATTLE " << unit->GetId() << " " << enemy->GetId() << " WINNER IS " << unit->GetId());
                    }
                    else if (unit->GetForce() == enemy->GetForce())
                    {
                        m_units.erase(unit->GetId());
                        m_units.erase(enemy->GetId());

                        LOG("[" << currentTick << "]" << "MARCH " << unit->GetId() << " FINISHED "
                            << task.destCoordinates.x << " " << task.destCoordinates.y
                            << " BATTLE " << unit->GetId() << " " << enemy->GetId() << " ALL DEAD ");

                        cell.isEmpty = true;
                    }
                    else
                    {
                        m_units.erase(unit->GetId());

                        LOG("[" << currentTick << "]" << "MARCH " << unit->GetId() << " FINISHED "
                            << unit->GetCoordinates().x << " " << unit->GetCoordinates().y
                            << " BATTLE " << unit->GetId() << " " << enemy->GetId() << " WINNER IS " << enemy->GetId());
                    }
                }
            }
            else
            {
                auto unit{ task.unit.lock() };
                unit->SetCoordinates(task.destCoordinates);
                cell.unit = unit;
                cell.isEmpty = false;

                LOG("[" << currentTick << "]" << "MARCH " << unit->GetId() << " FINISHED "
                    << unit->GetCoordinates().x << " " << unit->GetCoordinates().y);
            }

            return true;
        }
        return false;
    }

private:
    static inline size_t CurrentTick{ 0 };

    std::list<Task> m_tasks;
    std::map<UnitId, std::shared_ptr<core::unit::IUnit>> m_units;
    std::vector<std::vector<Cell>> m_field;

    core::Point m_boundary{ 0, 0 };
};

} // namespace

class Engine : public ICommandExecutor
{
public:
	virtual ~Engine() = default;

	Error Execute(const Command& command) final
	{
        if (command.name == CreateMapCommandName)
        {
            auto height{ std::atoll(command.args[0].c_str())};
            auto width{ std::atoll(command.args[1].c_str()) };
            m_field.ResetGameField({ height, width });
        }
        else if (command.name == SpawnCommandName)
        {
            auto id{ static_cast<size_t>(std::atoll((command.args[0].c_str()))) };
            auto x{ std::atoll((command.args[1].c_str())) };
            auto y{ std::atoll((command.args[2].c_str())) };
            auto force{ static_cast<size_t>(std::atoll((command.args[3].c_str()))) };
            m_field.AddUnit(id, force, Point{ x, y });
            m_field.DoOneTickForAllTasks();
        }
        else if (command.name == WaitCommandName)
        {
            auto ticks{ static_cast<size_t>(std::atoll(command.args[0].c_str())) };
            m_field.DoTicksForAllTasks(ticks);
        }
        else if (command.name == MarchCommandName)
        {
            auto id{ static_cast<size_t>(std::atoll(command.args[0].c_str())) };
            auto x{ std::atoll(command.args[1].c_str()) };
            auto y{ std::atoll(command.args[2].c_str()) };
            m_field.AddTask(id, { x, y });
            m_field.DoOneTickForAllTasks();
        }
        else if (command.name == FinishCommandName)
        {
            m_field.CompleteAllTasks();
        }
        else
        {
            return Error::UnknownCommand;
        }
		return Error::Ok;
	}

private:
    GameField m_field;
};

std::unique_ptr<ICommandExecutor> CreateCommandExecutor()
{
	return std::make_unique<Engine>();
}

} // namespace game::core::engine
