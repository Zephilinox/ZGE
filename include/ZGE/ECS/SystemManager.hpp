#ifndef SystemManager_HPP
#define SystemManager_HPP

//STD
#include <memory>
#include <unordered_map>
#include <cassert>

//3RD

//SELF
#include "ZGE/ECS/BaseSystem.hpp"
#include "ZGE/State/BaseState.hpp"

namespace zge
{

class SystemManager
{
public:
    SystemManager(std::shared_ptr<BaseState> stateOwner);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states);
    template <class T> void addSystem();

private:
    std::unordered_map<std::string, std::shared_ptr<BaseSystem>> m_systems;
    std::shared_ptr<BaseState> m_stateOwner;
};

template <class T>
void SystemManager::addSystem()
{
    std::shared_ptr<T> system(new T(m_stateOwner));

    if (!m_systems.count(system->ID))
    {
        m_systems[system->ID] = system;
    }
    else
    {
        assert(!"Error: That system already exists\n");
    }
}

} //ZGE

#endif //SystemManager_HPP
