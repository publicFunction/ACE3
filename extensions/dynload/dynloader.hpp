#pragma once

#include "shared.hpp"
#include "dispatch.hpp"
#include "arguments.hpp"

namespace ace {
    class dynloader : public singleton<dynloader> {
    public:
        bool load(const arguments & args_, std::string & result) {
            return false;
        }
        bool unload(const arguments & args_, std::string & result) {
            return false;
        }
        bool call(const arguments & args_, std::string & result) {
            return false;
        }
        
        bool register_functions() {
            dispatch::get().add("load", std::bind(&ace::dynloader::load, std::placeholders::_1, std::placeholders::_2));
            dispatch::get().add("unload", std::bind(&ace::dynloader::unload, std::placeholders::_1, std::placeholders::_2));
            dispatch::get().add("call", std::bind(&ace::dynloader::call, std::placeholders::_1, std::placeholders::_2));
        }

    };
};
