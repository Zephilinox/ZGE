#include "ZGE/Lua.hpp"

//STD
#include <iostream>

//SELF
#include "ZGE/Utility.hpp"

using namespace zge;

Lua::Lua()
{
    m_luaState = luaL_newstate();
    if (!m_luaState) throw std::runtime_error("The Lua state could not be constructed.\n");
}

Lua::~Lua()
{
    lua_close(m_luaState);
    m_luaState = nullptr;
}

int Lua::loadFile(std::string file)
{
    int error = luaL_loadfile(m_luaState, "variables.lua");

    if (error)
    {
        throw std::runtime_error(luaErrorAsString(m_luaState, error));
    }

    return error;
}

int Lua::executeFile(std::string file)
{
    int error = lua_pcall(m_luaState, 0, 0, 0);

    if (error)
    {
        throw std::runtime_error(luaErrorAsString(m_luaState, error));
    }

    return error;
}

lua_State* Lua::getRawState()
{
    return m_luaState;
}
