#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

//STD
#include <memory>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <vector>
#include <functional>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/ECS/BaseComponent.hpp"
#include "ZGE/State/BaseState.hpp"

namespace zge
{

typedef unsigned                                                            EntityID;
typedef std::unordered_map<std::string, std::shared_ptr<BaseComponent>>     EntityComponents;
typedef std::unordered_map<EntityID, EntityComponents>                      EntityMap;

class EntityManager
{
public:
    EntityManager(std::shared_ptr<BaseState> stateOwner);

    EntityID createEntity();
    bool entityExists(EntityID entID);
    void removeEntity(EntityID entID);

    template <class T> std::vector<unsigned> getEntitiesByComponent();
    template <class T, class... Other> std::vector<unsigned> getEntitiesByComponents();

    template <class T> T& addComponent(EntityID entID);
    template <class T> bool hasComponent(EntityID entID);
    template <class T1, class T2, class... Other> bool hasComponents(EntityID entID);
    template <class T> T& getComponent(EntityID entID);
    template <class T> std::vector<std::reference_wrapper<T>> getAllComponents();
    template <class T> void removeComponent(EntityID entID);

private:
    template <class T> bool hasComponents(EntityID entID);

    std::shared_ptr<BaseState> m_stateOwner;
    EntityMap m_entities;
};

template <class T>
std::vector<unsigned> EntityManager::getEntitiesByComponent()
{
    std::vector<unsigned> ents;

    for (auto& ent : m_entities)
    {
        if (hasComponent<T>(ent.first))
        {
            ents.push_back(ent.first);
        }
    }

    return ents;
}

template <class T, class... Other>
std::vector<unsigned> EntityManager::getEntitiesByComponents()
{
    std::vector<unsigned> ents;

    for (auto& ent : m_entities)
    {
        if (hasComponents<T, Other...>(ent.first))
        {
            ents.push_back(ent.first);
        }
    }

    return ents;
}

template <class T>
T& EntityManager::addComponent(EntityID entID)
{
    auto component = std::shared_ptr<T>(new T);

    //Check if this component's ID isn't the default for the base component
    //If it is then either they are adding a useless component, or they forgot to specify a new ID for the component they are trying to add
    //I'm only doing the check here, rather than in every function, since every component used will eventually need to be added to an entity

    if (component->ID == BaseComponent("Base").ID)
    {
        std::cout << "\n" << "addComponent: Attempted to add the BaseComponent" << "\n";
        assert(!"Perhaps you forgot to assign a new ID in this components initialization list?");
    }

    if (!hasComponent<T>(entID))
    {
        m_entities[entID][component->ID] = component;
        return getComponent<T>(entID);
    }
    else
    {
        assert(!"addComponent: That Component already exists");
    }
}

template <class T>
bool EntityManager::hasComponent(EntityID entID)
{
    T component;

    if (entityExists(entID))
    {
        return m_entities[entID].count(component.ID);
    }
    else
    {
        std::cout << entID << "\n";
        assert(!"hasComponent: That Entity ID is invalid");
        return false;
    }
}

template <class T> bool EntityManager::hasComponents(EntityID entID)
{
    return hasComponent<T>(entID);
}

template <class T1, class T2, class... Other>
bool EntityManager::hasComponents(EntityID entID)
{
    if (entityExists(entID))
    {
        return (hasComponent<T1>(entID) && hasComponents<T2, Other...>(entID));
    }
    else
    {
        assert(!"hasComponents: That Entity ID is invalid");
        return false;
    }
}


template <class T>
T& EntityManager::getComponent(EntityID entID)
{
    T component;

    if (hasComponent<T>(entID))
    {
        return *(std::static_pointer_cast<T>(m_entities[entID][component.ID]));
    }
    else
    {
        assert(!"getComponent: The Entity does not have that Component");
    }
}

template <class T>
std::vector<std::reference_wrapper<T>> EntityManager::getAllComponents()
{
    std::vector<std::reference_wrapper<T>> components;

    std::cout << "2Size: " << m_entities.size() << "\n";

    /*for (auto& ent : m_entities)
    {
        std::cout << ent.first << "\n";
        if (hasComponent<T>(ent.first))
        {
            auto comp1 = std::static_pointer_cast<T>(m_entities[ent.first][T().ID]);
            std::reference_wrapper<T> comp2 = std::ref(*comp1.get());

            components.push_back(comp2);
        }
    }*/

    /*for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        EntityID entID = it->first;

        std::cout << entID << "\n";

        /*if (hasComponent<T>(entID))
        {
            auto comp1 = std::static_pointer_cast<T>(m_entities[entID][T().ID]);
            std::reference_wrapper<T> comp2 = std::ref(*comp1.get());

            components.push_back(comp2);
        }*/
    //}

    return components;
}

template <class T>
void EntityManager::removeComponent(EntityID entID)
{
    T component;

    if (hasComponent<T>(entID))
    {
        m_entities[entID].erase(component.ID);
    }
    else
    {
        assert(!"removeComponent: The Entity does not have that Component");
    }
}

} //ZGE

#endif //ENTITYMANAGER_HPP
