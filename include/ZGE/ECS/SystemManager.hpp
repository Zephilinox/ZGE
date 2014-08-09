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
    SystemManager(std::reference_wrapper<sf::RenderWindow> window, std::reference_wrapper<EntityManager> entMan);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states);
    template <class T> void addSystem();

private:
    std::unordered_map<std::string, std::shared_ptr<BaseSystem>> m_systems;
    std::reference_wrapper<sf::RenderWindow> m_window;
    std::reference_wrapper<EntityManager> m_entMan;
};

template <class T>
void SystemManager::addSystem()
{
    std::shared_ptr<T> system(new T(std::ref(m_window), std::ref(m_entMan)));

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
