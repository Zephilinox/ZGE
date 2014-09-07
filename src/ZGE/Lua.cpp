#include "ZGE/Lua.hpp"

//STD
#include <iostream>

//SELF
#include "ZGE/Utility.hpp"

using namespace zge;

Lua::Lua()
{
    m_luaState = luaL_newstate();
}

int Lua::loadFile(std::string file)
{
    int error = luaL_loadfile(m_luaState, "variables.lua");

    if (error)
    {
        switch (error)
        {
            case LUA_ERRSYNTAX:
            {
                std::cout << "Syntax Error: " + std::string(lua_tostring(m_luaState, -1)) << "\n";
                break;
            }

            case LUA_ERRFILE:
            {
                std::cout << "Could not find file '" << file << "'\n";
                break;
            }

            default:
            {
                std::cout << "ErrorCode = " + zge::toString(error) << "\n";
                break;
            }
        }
    }

    return error;
}

int Lua::executeFile(std::string file)
{
    int error = lua_pcall(m_luaState, 0, 0, 0);

    if (error)
    {
        switch (error)
        {
            case LUA_ERRRUN:
            {
                std::cout << "Runtime Error: " + std::string(lua_tostring(m_luaState, -1)) << "\n";
                break;
            }

            case LUA_ERRMEM:
            {
                std::cout << "Memory Allocation Error\n";
                break;
            }

            case LUA_ERRERR:
            {
                std::cout << "Error while running error handler\n";
                break;
            }

            default:
            {
                std::cout << "ErrorCode" + zge::toString(error) << "\n";
            }
        }
    }

    return error;
}

lua_State* Lua::getRawState()
{
    return m_luaState;
}
