#include "p3d/model.hpp"
#include <sstream>

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {
        skeleton::skeleton() : size(0) {}
        skeleton::skeleton(std::fstream & stream_, const uint32_t lod_count) {
            READ_STRING(name);
            
            READ_BOOL(inherited);
            READ_DATA(size, sizeof(uint32_t));

            for (int x = 0; x < size; x++) {
                std::string name, parent;
                
                READ_STRING(name);
                READ_STRING(parent);

                bone tbone(name, parent);
                bones[name] = tbone;
            }

            // Skip a byte because!
            //stream_.seekg(1, stream_.cur);
        }
        skeleton::~skeleton() {}
    }
}
