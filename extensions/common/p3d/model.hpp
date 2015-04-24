#pragma once

#include "ace_common.h"

#include "animation.hpp"
#include "skeleton.hpp"
#include "model_info.hpp"

namespace ace {
    namespace p3d {
        class model {
        public:
            model();
            model(std::fstream &, const std::string &filename_ = "");
            ~model();

            size_t                              size;
            model_info                          info;
            skeleton                            *skeleton;
            std::vector<std::vector<uint32_t>>  bones2anims;
            std::vector<animate_bone>           anims2bones;

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