#pragma once
#pragma once

#include "ace_common.h"


namespace ace {
    namespace p3d {
        class bone {
        public:
            bone() : name(""), parent("") {}
            bone(const std::string & name_, const std::string & parent_)
                : name(name_), parent(parent_) {
            }
            std::string name;
            std::string parent;
            std::vector<std::string> children;
            std::vector<uint32_t> animations;
        };

        class skeleton {
        public:
            skeleton();
            skeleton(std::fstream &, const uint32_t lod_count);
            ~skeleton();

            std::string name;
            bool inherited;
            uint32_t size;
            std::map<std::string, bone> root_bones;
            std::vector<bone> all_bones;
        };
    };
};