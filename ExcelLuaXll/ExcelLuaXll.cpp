
#include "stdafx.h"
#include "LuaFuncs.h"

#define rgWorksheetFuncsRows 3
#define rgWorksheetFuncsCols 14

static LPWSTR rgWorksheetFuncs[rgWorksheetFuncsRows][rgWorksheetFuncsCols] =
{

    {
        L"LUA_ExecFunc",
        L"BCBB",
        L"Lua.ExecFun",
        L"LuaFuncName, Num1, Num2",
        L"1",
        L"Lua Add-In",
        L"",
        L"",
        L"Executes the passed function name in Lua ancilary script.",
        L"Lua function name in ancilary script",
        L"First numeric parameter to Lua script.",
        L"Second numeric parameter to Lua script.",
        L"",
        L""
    }

};

// Excel calls xlAutoOpen when it loads the XLL.
__declspec(dllexport) int WINAPI xlAutoOpen(void)
{
    static XLOPER12 xDLL;   /* name of this DLL */
    int i;                  /* Loop index */

    /*
    ** In the following block of code the name of the XLL is obtained by
    ** calling xlGetName. This name is used as the first argument to the
    ** REGISTER function to specify the name of the XLL. Next, the XLL loops
    ** through the rgFuncs[] table, registering each function in the table using
    ** xlfRegister. Functions must be registered before you can add a menu
    ** item.
    */

    Excel12f(xlGetName, &xDLL, 0);

    for (i = 0; i < rgWorksheetFuncsRows; i++)
    {
        Excel12f(xlfRegister, 0, 1 + rgWorksheetFuncsCols,
            (LPXLOPER12)&xDLL,
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][0]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][1]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][2]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][3]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][4]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][5]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][6]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][7]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][8]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][9]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][10]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][11]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][12]),
            (LPXLOPER12)TempStr12(rgWorksheetFuncs[i][13]));
    }

    /* Free the XLL filename */
    Excel12f(xlFree, 0, 1, (LPXLOPER12)&xDLL);

    return 1;
}


double WINAPI LUA_ExecFunc(char* luaFuncName, double a, double b)
{
    return ExecLuaFunc(luaFuncName, a, b);
}