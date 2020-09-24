#include "stdafx.h"
#include <iostream>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

std::string GetUserHomeDirectory()
{
    char* buf = nullptr;
    size_t size = 0;

    if (_dupenv_s(&buf, &size, "USERPROFILE") == 0 && buf != nullptr)
    {
        std::string path = std::string(buf);
        free(buf);
        return path;
    }

    return ".";
}

double ExecLuaFunc(char* luaFuncName, double num1, double num2)
{
    double funcResult = 0;

    const std::string user_home_path = GetUserHomeDirectory();
    const std::string luaScriptFile = user_home_path + "/luascript.lua";

    lua_State* L = luaL_newstate();

    int luaResult = luaL_dofile(L, luaScriptFile.c_str());

    if (luaResult == LUA_OK)
    {
        lua_getglobal(L, luaFuncName);

        if (lua_isfunction(L, -1))
        {
            lua_pushnumber(L, num1);
            lua_pushnumber(L, num2);
            luaResult = lua_pcall(L, 2, 1, 0);

            if (luaResult == LUA_OK)
            {
                funcResult = lua_tonumber(L, -1);
            }
        }
    }

    lua_close(L);
    return funcResult;
}