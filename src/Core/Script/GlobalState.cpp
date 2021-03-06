#include <Bindings/Bindings.hpp>
#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe::Script
{
    kaguya::State ScriptEngine;
    void InitScriptEngine()
    {
        System::Path("Lib/Internal/LuaCore.lua").loadResource(&ScriptEngine, System::Loaders::luaLoader);
        System::Path("Lib/Internal/Environment.lua").loadResource(&ScriptEngine, System::Loaders::luaLoader);
        System::Path("Lib/Internal/ScriptInit.lua").loadResource(&ScriptEngine, System::Loaders::luaLoader);
        System::Path("Lib/Internal/Triggers.lua").loadResource(&ScriptEngine, System::Loaders::luaLoader);
        Bindings::BindTree(&ScriptEngine);
        ScriptEngine["Hook"] = kaguya::NewTable();
        ScriptEngine.dofile("Lib/Internal/Canvas.lua");
    }

    unsigned int CreateNewEnvironment()
    {
        return ScriptEngine["LuaCore"]["CreateNewEnv"]();
    }

    void executeFile(unsigned int envIndex, const std::string& file)
    {
        ScriptEngine["LuaCore"]["ExecuteFileOnEnv"](System::Path(file).find(), envIndex);
    }

    void executeString(unsigned int envIndex, const std::string& string)
    {
        ScriptEngine["LuaCore"]["ExecuteStringOnEnv"](string, envIndex);
    }
}
