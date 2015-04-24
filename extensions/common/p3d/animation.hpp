#pragma once

#include "ace_common.h"
#include "vector.hpp"

namespace ace {
    namespace p3d {
        class animation {
        public:
            animation();
            animation(std::fstream &);
            ~animation();

            uint32_t        type;
            std::string     name;  // "RightDoor"
            std::string     source;     // "rotor"
            float           minmax_value[2];
            float           minmax_phase[2];
            uint32_t        source_address;
            uint32_t        null;
            uint32_t        floats_count; //always 2
            float           *floats;

            std::vector<float> transforms;
        };
    };
};