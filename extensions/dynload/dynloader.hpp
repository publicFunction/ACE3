#pragma once

#include "shared.hpp"
#include "dispatch.hpp"
#include "arguments.hpp"

typedef void (*__stdcall RVExtension)(char *output, int outputSize, const char *function);

namespace ace {

    class module {
    public:
        module() : handle(nullptr), function(nullptr), name("") {}
        module(std::string name_, HANDLE handle_, RVExtension function_) : handle(nullptr), function(function_), name(name_) {}

        std::string name;
        HINSTANCE   handle;
        RVExtension function;
    };

    class dynloader : public singleton<dynloader> {
    public:
        dynloader() {}
        ~dynloader() {
            for (auto & kv : _modules) {
                arguments temp(kv.first);
                std::string result_temp;
                unload(temp, result_temp);
            }
        }

#ifdef _WINDOWS
        bool load(const arguments & args_, std::string & result) {
            HINSTANCE dllHandle;
            RVExtension function;

            if (_modules.find(args_.as_string(0)) != _modules.end()) {
                return true;
            }

            dllHandle = LoadLibrary(args_.as_string(0).c_str());
            if (!dllHandle)
                return false;

            function = (RVExtension)GetProcAddress(dllHandle, "RVExtension");
            if (!function) {
                FreeLibrary(dllHandle);
            }

            _modules[args_.as_string(0)] = module(args_.as_string(0), dllHandle, function);

            return false;
        }
        bool unload(const arguments & args_, std::string & result) {

            if (_modules.find(args_.as_string(0)) != _modules.end()) {
                return true;
            }

            FreeLibrary(_modules[args_.as_string(0)].handle);
            _modules.erase(args_.as_string(0));

            return false;
        }
#endif

        bool call(const arguments & args_, std::string & result) {
            if (_modules.find(args_.as_string(0)) == _modules.end()) {
                return false;
            }

            result = "";
            result.resize(4096);

            std::string function_str;
            std::vector<std::string> temp = ace::split(args_.get(), ',');

            for (int x = 1; x < temp.size(); x++)
                function_str = function_str + temp[x] + ",";

            _modules[args_.as_string(0)].function((char *)result.c_str(), 4096, (const char *)function_str.c_str());

            return true;
        }
        
        bool register_functions() {
            dispatch::get().add("load", std::bind(&ace::dynloader::load, this, std::placeholders::_1, std::placeholders::_2));
            dispatch::get().add("unload", std::bind(&ace::dynloader::unload, this, std::placeholders::_1, std::placeholders::_2));
            dispatch::get().add("call", std::bind(&ace::dynloader::call, this, std::placeholders::_1, std::placeholders::_2));

            return true;
        }
    protected:
        std::map<std::string, module> _modules;
    };
};
