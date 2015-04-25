#pragma once

#include "ace_common.h"

#include "animation.hpp"
#include "skeleton.hpp"
#include "model_info.hpp"
#include "lod_info.hpp"

namespace ace {
    namespace p3d {
        class face_settings {
        public:
            face_settings() {}
            face_settings(std::fstream &stream_) {
                stream_.read((char *)&count, sizeof(uint32_t));
                stream_.read((char *)&unknown, sizeof(uint8_t) * 21);
            }

            uint32_t    count;
            uint8_t     unknown[21];
        };

        class model {
        public:
            model();
            model(std::fstream &, const std::string &filename_ = "");
            ~model();

            // LOD info
            bool                                *useFaceDefaults;
            std::vector<face>                   defaultFaces;
            std::vector<lod_info>               lods;

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