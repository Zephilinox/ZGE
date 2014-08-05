#ifndef RESOURCE_HPP
#define RESOURCE_HPP

//STD
#include <string>
#include <memory>

//3RD
#include <SFML/Audio.hpp>

//SELF
#include "ResourceManager.hpp"

namespace zge
{

template <class ResourceType>
class Resource
{
public:
    Resource(std::string n);
    ~Resource();

    Resource(const Resource& res);
    Resource& operator=(const Resource& res);
    operator ResourceType&() const;
    ResourceType* operator->();

    ResourceType& get();

private:
    void copyResource(const Resource<ResourceType>& res);

    std::string m_name;
};

//Templated functions
template <class ResourceType>
Resource<ResourceType>::Resource(std::string n)
    : m_name(n)
{
    std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_name << "\n";
    if (ResourceManager<ResourceType>::getInstance().create(m_name))
    {
        assert(ResourceManager<ResourceType>::getInstance().get(m_name).loadFromFile(m_name));
    }
}

template <class ResourceType>
Resource<ResourceType>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_name << "\n";
    ResourceManager<ResourceType>::getInstance().destroy(m_name);
}

template <class ResourceType>
Resource<ResourceType>::Resource(const Resource<ResourceType>& res)
{
    this->copyResource(res);
}

template <class ResourceType>
Resource<ResourceType>& Resource<ResourceType>::operator=(const Resource<ResourceType>& res)
{
    this->copyResource(res);
    return *this;
}

template <class ResourceType>
Resource<ResourceType>::operator ResourceType&() const
{
    return ResourceManager<ResourceType>::getInstance().get(m_name);
}

template <class ResourceType>
ResourceType* Resource<ResourceType>::operator->()
{
    return &get();
}

template <class ResourceType>
ResourceType& Resource<ResourceType>::get()
{
    return ResourceManager<ResourceType>::getInstance().get(m_name);
}

template <class ResourceType>
void Resource<ResourceType>::copyResource(const Resource<ResourceType>& res)
{
    //std::cout << "[Resource] Copied\n";
    //std::cout << "\tthis = " << m_name << "\n\tother = " << res.m_name << "\n";

    if (res.m_name.empty()) return;

    if (!m_name.empty())
    {
        ResourceManager<ResourceType>::getInstance().destroy(m_name); //Destroy whatever resource this was holding before
    }

    m_name = res.m_name;
    ResourceManager<ResourceType>::getInstance().create(m_name); //Increase reference count
}

/*
*
*
* sf::Sound specialization
*
*
*/
template <>
class Resource<sf::Sound>
{
public:
    Resource(std::string n);
    ~Resource();

    Resource(const Resource<sf::Sound>& res);
    Resource<sf::Sound>& operator=(const Resource<sf::Sound>& res);

    sf::Sound& get();

private:
    void copyResource(const Resource<sf::Sound>& res);

    std::string m_name;
    sf::Sound m_sound;
    static unsigned int m_globalSoundInstances;
};

/*
*
*
* sf::Music specialization
*
*
*/
template <>
class Resource<sf::Music>
{
public:
    Resource(const Resource<sf::Music>& res) = delete;
    Resource<sf::Music>& operator=(const Resource<sf::Music>& res) = delete;

    Resource(std::string n);
    ~Resource();

    sf::Music& get();

private:
    std::string m_name;
    sf::Music m_music;
    static unsigned int m_globalMusicInstances;
};

} //ZGE

#endif //RESOURCE_HPP
