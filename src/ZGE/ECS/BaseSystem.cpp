#include "ZGE/ECS/BaseSystem.hpp"

BaseSystem::BaseSystem(std::string id, std::shared_ptr<EntityManager> entMan)
    : ID(id)
    , m_entMan(entMan)
{
}

