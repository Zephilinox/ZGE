#ifndef BASESYSTEM_HPP
#define BASESYSTEM_HPP

//STD
#include <string>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/ECS/EntityManager.hpp"

class BaseSystem
{
public:
    BaseSystem(std::string id, std::shared_ptr<EntityManager> entMan);
    virtual ~BaseSystem() = default;

    virtual void handleEvent(const sf::Event& event){};
    virtual void update(float dt){};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states){};

    std::string ID;

protected:
    std::shared_ptr<EntityManager> m_entMan;
};

#endif //BASESYSTEM_HPP
