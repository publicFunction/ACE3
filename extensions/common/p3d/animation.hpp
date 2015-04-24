#pragma once

#include "ace_common.h"
#include "vector.hpp"

namespace ace {
    namespace p3d {
         
        class animate_bone {
        public:
            animate_bone() : index(-1) {}
            uint32_t index;
            uint32_t lod;
            ace::vector3<float> axis_direction;
            ace::vector3<float> axis_position;
        };


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
            
            std::vector<float> transforms;
            std::vector<animate_bone> bones;
            


            //uint32_t        null;
            //uint32_t        floats_count; //always 2
            //float           *floats;

            //float transforms[4];
            //float angles[2];
            //float offsets[2];
            //float hide;

            //ace::vector3<float> axis_pos;
            //ace::vector3<float> axis_dir;
        };
    };
};