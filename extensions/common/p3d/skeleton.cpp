#include "p3d/model.hpp"
#include <sstream>

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {
        skeleton::skeleton() : size(0) {}
        skeleton::skeleton(std::fstream & stream_, const uint32_t lod_count) {
            READ_STRING(name);
            if (name.length() > 1) {
                READ_BOOL(inherited);
                stream_.read((char *)&size, sizeof(uint32_t));

                for (int x = 0; x < size; x++) {
                    std::string _name, _parent;

                    READ_STRING(_name);
                    READ_STRING(_parent);

                    bone tbone(_name, _parent);
                    bones[name] = tbone;
                }

                // Skip a byte because!
                //stream_.seekg(1, stream_.cur);
                LOG(DEBUG) << "Skeleton loaded: " << name;
            }
        }
        skeleton::~skeleton() {}
    }
}
