#pragma once

#include "ace_common.h"

#include "animation.hpp"
#include "skeleton.hpp"
#include "model_info.hpp"
#include "lod_data.hpp"

namespace ace {
    namespace p3d {
        typedef struct face {
            face() {}
            uint32_t    HeaderFaceCount;
            uint32_t    aDefaultLong;     //ffffffff or 6f 7a 80 fa eg
            uint8_t     UnknownByte;      //generally zero
            uint8_t     aFlag;
            uint8_t     Zeroes[7];
        } face;

        class model {
        public:
            model();
            model(std::fstream &, const std::string &filename_ = "");
            ~model();

            // LOD info
            bool                                *useFaceDefaults;
            std::vector<face>                   defaultFaces;
            std::vector<lod_data>               lods;

            size_t                              size;
            model_info                          info;
            skeleton                            *skeleton;

            bool                    has_animations;
            std::vector<animation>  animations;
            

            std::vector<uint32_t>   start_lod;
            std::vector<uint32_t>   end_lod;

            // data root fileds
            std::string     filename;
            uint32_t        lod_count;
            uint32_t        filetype;
            uint64_t        version;
            std::string     prefix_name;

        };
    };
};