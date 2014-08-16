#include "ZGE/ECS/EntityManager.hpp"

using namespace zge;

EntityManager::EntityManager(std::shared_ptr<BaseState> stateOwner)
    : m_stateOwner(stateOwner)
{
}

EntityID EntityManager::createEntity()
{
    EntityID entID = 1; //Reserve 0 just in case we need it for some kind of error handling in the future

    while (entityExists(entID))
    {
        entID++;
    }

    m_entities[entID];

    return entID;
}

bool EntityManager::entityExists(unsigned entID)
{
    return m_entities.count(entID);
}

void EntityManager::removeEntity(unsigned entID)
{
    if (m_entities.count(entID))
    {
        assert(!"Error: That Entity does not exist");
    }
    else
    {
        m_entities.erase(entID);
    }
}
