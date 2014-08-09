#include "ZGE/ECS/SystemManager.hpp"

using namespace zge;

SystemManager::SystemManager(std::reference_wrapper<sf::RenderWindow> window, std::reference_wrapper<EntityManager> entMan)
    : m_window(window)
    , m_entMan(entMan)
{
    m_entMan.get().entityExists(0);
}

void SystemManager::handleEvent(const sf::Event& event)
{
    for (auto& sys : m_systems)
    {
        sys.second->handleEvent(event);
    }
}

void SystemManager::update(float dt)
{
    for (auto& sys : m_systems)
    {
        sys.second->update(dt);
    }
}

void SystemManager::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    for (auto& sys : m_systems)
    {
        sys.second->draw(target, states);
    }
}
