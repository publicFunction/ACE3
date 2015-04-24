#pragma once
#pragma once

#include "ace_common.h"

namespace ace {
    namespace p3d {
        class skeleton {
        public:
            skeleton();
            skeleton(std::fstream &, const uint32_t lod_count);
            ~skeleton();

            std::string name;
            bool inherited;
            std::map<std::string, std::string> bones;
        };
    };
};