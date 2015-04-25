#include "lod_info.hpp"

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {


        lod_info::lod_info() {}
        lod_info::lod_info(std::fstream & stream_) {
            uint32_t temp_count;

            // proxies
            stream_.read((char *)&temp_count, sizeof(uint32_t));
            for (int x = 0; x < temp_count; x++) {
                proxies.push_back(lod_proxy(stream_));
            }

            // items
            stream_.read((char *)&temp_count, sizeof(uint32_t));
            for (int x = 0; x < temp_count; x++) {
                // @ TODO: LodItems
            }

            // bone links
            stream_.read((char *)&temp_count, sizeof(uint32_t));
            for (int x = 0; x < temp_count; x++) {
                // @ TODO: BoneLInks
                uint32_t link_count;
                std::vector<uint32_t> links;
                stream_.read((char *)&link_count, sizeof(uint32_t));
                for (int x = 0; x < link_count; x++) {
                    uint32_t val;
                    stream_.read((char *)&val, sizeof(uint32_t));
                    links.push_back(val);
                }
                bone_links.push_back(links);
            }

            stream_.read((char *)&point_count, sizeof(uint32_t));
            stream_.read((char *)&point_count_2, sizeof(uint32_t));
            point_flags = compressed_fill<uint32_t>(stream_);
        }
        lod_info::~lod_info() {}

    //uint32_t                size;
    // bool                    fill;
    //std::vector<uint8_t>    data;


        lod_proxy::lod_proxy() { }
        lod_proxy::lod_proxy(std::fstream &stream_) {
            READ_STRING(name);
            transform = ace::transform_matrix(stream_);
            stream_.read((char *)&sequence_id, sizeof(uint32_t));
            stream_.read((char *)&named_selection_id, sizeof(uint32_t));
            stream_.read((char *)&bone_id, sizeof(uint32_t));
            stream_.read((char *)&section_id, sizeof(uint32_t));

        }
    }
}