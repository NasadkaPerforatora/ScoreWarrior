#include "warrior.h"

namespace game::core::unit {

class Warrior : public IUnit
{
public:
    explicit Warrior(const WarriorSettings& settings)
        : m_id(settings.id)
        , m_force(settings.force)
        , m_coordinates(settings.coordinates)
    {
    }

    virtual ~Warrior() = default;

    size_t GetId() const final
    {
        return m_id;
    }

    size_t GetForce() const final
    {
        return m_force;
    }

    core::Point GetCoordinates() const final
    {
        return m_coordinates;
    }

    void SetCoordinates(const core::Point coordinates) final
    {
        m_coordinates = coordinates;
    }

private:
    const size_t m_id;
    const size_t m_force;
    core::Point m_coordinates;
};

std::shared_ptr<IUnit> CreateWarrior(const WarriorSettings& settings)
{
    return std::make_shared<Warrior>(settings);
}

} // namespace game::core::unit
