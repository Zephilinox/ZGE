#include "ZGE/ECS/SystemManager.hpp"

SystemManager::SystemManager(std::shared_ptr<EntityManager> entMan)
    : m_entMan(entMan)
{
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
