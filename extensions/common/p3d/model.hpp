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

            size_t          size;
            model_info      info;
            skeleton        *skeleton;

            bool                    has_animations;
            std::vector<animation>  animations;

            // data root fileds
            std::string     filename;
            uint32_t        lod_count;
            uint32_t        filetype;
            uint64_t        version;
            std::string     prefix_name;
        };
    };
};