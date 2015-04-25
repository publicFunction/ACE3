#include "lod_data.hpp"

#include "read_helper.hpp"

namespace ace {
    namespace p3d {
        lod_data::lod_data() {}
        lod_data::lod_data(std::fstream & stream_) {
            uint32_t proxy_count;

            stream_.read((char *)&proxy_count, sizeof(uint32_t));
            for (int x = 0; x < proxy_count; x++) {
                
            }
        }
        ~lod_data() {}
    }
}