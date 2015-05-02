#pragma once

#include "shared.hpp"
#include "dispatch.hpp"
#include "arguments.hpp"

typedef void (*__stdcall RVExtension)(char *output, int outputSize, const char *function);

namespace ace {
    class module {
    public:
        module() : handle(INVALID_HANDLE_VALUE), function(nullptr), name("") {}
        module(std::string name_, HANDLE handle_, RVExtension function_) : handle(handle_), function(function_), name(name_) {}

        std::string name;
        HANDLE      handle;
        RVExtension function;
    };

    class dynloader : public singleton<dynloader> {
    public:
        bool load(const arguments & args_, std::string & result) {
            
            

            return false;
        }
        bool unload(const arguments & args_, std::string & result) {


            return false;
        }
        bool call(const arguments & args_, std::string & result) {
            if (_modules.find(args_.as_string(0)) == _modules.end()) {
                return false;
            }
            std::string output, function_str;
            output.resize(4096);

            function_str = args_.get();
            
            _modules[args_.as_string(0)].function((char *)output.c_str(), 4096, (const char *)function_str.c_str());
        }
        
        bool register_functions() {
            dispatch::get().add("load", std::bind(&ace::dynloader::load, std::placeholders::_1, std::placeholders::_2));
            dispatch::get().add("unload", std::bind(&ace::dynloader::unload, std::placeholders::_1, std::placeholders::_2));
            dispatch::get().add("call", std::bind(&ace::dynloader::call, std::placeholders::_1, std::placeholders::_2));
        }
    protected:
        std::map<std::string, module> _modules;
    };
};
