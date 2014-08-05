#ifndef RESOURCECACHE_HPP
#define RESOURCECACHE_HPP

//STD
#include <map>
#include <memory>
#include <string>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Resource.hpp"

namespace zge
{

template <class ResourceType>
class ResourceCache
{
public:
    ResourceCache();
    ~ResourceCache();
    ResourceCache<ResourceType>(const ResourceCache<ResourceType>&) = delete;
    ResourceCache<ResourceType>& operator=(const ResourceCache<ResourceType>&) = delete;

    ResourceType& get(std::string name);

    void add(std::string name, std::string path);
    void remove(std::string name);
    void removeAll();

private:
    std::map<std::string, std::unique_ptr<Resource<ResourceType>>> m_resources;
};

//Template functions
template <class ResourceType>
ResourceCache<ResourceType>::ResourceCache()
{
    //std::cout << "[ResourceCache] Constructor \n";
}

template <class ResourceType>
ResourceCache<ResourceType>::~ResourceCache()
{
    //std::cout << "[ResourceCache] Destructor \n";

    this->removeAll();
}

template <class ResourceType>
ResourceType& ResourceCache<ResourceType>::get(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    assert(m_resources.count(name));
    return m_resources[name].get();
}

template <class ResourceType>
void ResourceCache<ResourceType>::add(std::string name, std::string path)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    std::transform(path.begin(), path.end(), path.begin(), ::tolower);

    m_resources[name].reset(new Resource<ResourceType>(path));
}

template <class ResourceType>
void ResourceCache<ResourceType>::remove(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = m_resources.find(name);
    assert(it != m_resources.end());
    m_resources.erase(it);
}

template <class ResourceType>
void ResourceCache<ResourceType>::removeAll()
{
    m_resources.clear();
}

/*
*
*
* sf::Sound Specialization
*
*
*/
/*
template <>
class ResourceCache<sf::Sound>
{
public:
    ResourceCache();
    ~ResourceCache();
    ResourceType& get(std::string name);

    void add(std::string name, std::string path);
    void remove(std::string name);
    void removeAll();

private:
    std::map<std::string, std::unique_ptr<Resource<sf::Sound>>> m_resources;
};*/

#include "ResourceManagement/ResourceCache.inl"

} //ZGE

#endif //RESOURCECACHE_HPP
