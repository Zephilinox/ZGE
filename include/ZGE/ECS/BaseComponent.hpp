#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP

//STD
#include <unordered_map>

//3RD

//SELF

class BaseComponent
{
public:
    BaseComponent(std::string id);
    virtual ~BaseComponent() = default;

    std::string ID;
};

#endif //BASECOMPONENT_HPP
