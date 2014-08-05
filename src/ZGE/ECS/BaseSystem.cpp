#include "ZGE/ECS/BaseSystem.hpp"

using namespace zge;

BaseSystem::BaseSystem(std::string id, std::shared_ptr<BaseState> stateOwner)
    : ID(id)
    , m_stateOwner(stateOwner)
{
}

