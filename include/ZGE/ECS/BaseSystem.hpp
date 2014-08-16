#ifndef BASESYSTEM_HPP
#define BASESYSTEM_HPP

//STD
#include <string>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/ECS/EntityManager.hpp"
#include "ZGE/State/BaseState.hpp"

namespace zge
{

class BaseSystem
{
public:
    BaseSystem(std::string id, std::shared_ptr<BaseState> stateOwner);
    virtual ~BaseSystem() = default;

    virtual void handleEvent(const sf::Event& event){};
    virtual void update(float dt){};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states){};

    std::string ID;

protected:
    std::shared_ptr<BaseState> m_stateOwner;
};

} //ZGE

#endif //BASESYSTEM_HPP
