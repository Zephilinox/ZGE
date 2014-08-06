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
    BaseSystem(std::string id, std::reference_wrapper<sf::RenderWindow> window, std::reference_wrapper<EntityManager> entMan);
    virtual ~BaseSystem() = default;

    virtual void handleEvent(const sf::Event& event){};
    virtual void update(float dt){};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states){};

    std::string ID;

protected:
    std::reference_wrapper<sf::RenderWindow> m_window;
    std::reference_wrapper<EntityManager> m_entMan;
};

} //ZGE

#endif //BASESYSTEM_HPP
