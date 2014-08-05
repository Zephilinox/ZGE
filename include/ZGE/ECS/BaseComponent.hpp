#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP

//STD
#include <unordered_map>

//3RD

//SELF

namespace zge
{

class BaseComponent
{
public:
    BaseComponent(std::string id);
    virtual ~BaseComponent() = default;

    std::string ID;
};

} //ZGE


#endif //BASECOMPONENT_HPP
