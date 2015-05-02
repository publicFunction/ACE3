#pragma once

#include "shared.hpp"
#include "vector.hpp"

#include <vector>
#include <string>

namespace ace {
    class arguments {
    public:
        arguments(const std::string & str) : _original(str) {
            _args = ace::split(str, ',');
        }

        size_t size() const { return _args.size(); }

        const std::string & operator[] (uint32_t index) const { return _args[index]; }

        const std::string & as_string(uint32_t _index) const { return _args[_index]; }
        float as_float(uint32_t _index) const { return atof(_args[_index].c_str()); }
        int as_int(uint32_t _index) const { return atoi(_args[_index].c_str()); }
        int as_uint32(uint32_t _index) const { return (uint32_t)atoi(_args[_index].c_str()); }
        ace::vector3<float> as_vector(uint32_t _index) const {
            std::vector<std::string> t = ace::split(_args[_index], ';');
            return ace::vector3<float>(atof(t[0].c_str()),
                atof(t[1].c_str()),
                atof(t[2].c_str()));
        }

        const std::string & get() const {
            return _original;
        }

    protected:
        std::vector<std::string> _args;
        const std::string        &_original;
    };
}