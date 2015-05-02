#pragma once

#include "shared.hpp"
#include "arguments.hpp"
#include "singleton.hpp"

namespace ace {
    class dispatch : public singleton<dispatch> {
    public:
        bool call(const std::string & name_, const arguments & args_, std::string & result_) {
            if (_methods.find(name_) == _methods.end()) {
                // @TODO: Exceptions
                return false;
            }
            return _methods[name_](args_, result_);
        }

        bool add(const std::string & name_, std::function<bool(const arguments &, std::string &)> func_) {
            _methods[name_] = func_;
        }
    protected:
        std::map < std::string, std::function<bool(const arguments &, std::string &)> > _methods;
    };
};