#include "ZGE/ECS/BaseSystem.hpp"

using namespace zge;

BaseSystem::BaseSystem(std::string id, std::reference_wrapper<sf::RenderWindow> window, std::reference_wrapper<EntityManager> entMan)
    : ID(id)
    , m_window(window)
    , m_entMan(entMan)
{
}

