#include "lod_info.hpp"

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {


        lod_info::lod_info() {}
        lod_info::lod_info(std::fstream & stream_) {
            uint32_t temp_count;

            // proxies
            stream_.read((char *)&temp_count, sizeof(uint32_t)); assert(temp_count < 4096 * 10);
            for (int x = 0; x < temp_count; x++) {
                proxies.push_back(proxy(stream_));
            }
            LOG(DEBUG) << "Found Proxies:";
            for (auto & proxy : proxies) {
                LOG(DEBUG) << "\t" << proxy.name;
            }
            
            compressed_fill<uint32_t> item(stream_, false, false);
            items = item.data;

            // bone links
            stream_.read((char *)&temp_count, sizeof(uint32_t)); assert(temp_count < 4096 * 10);
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
            

            stream_.read((char *)&u_float_1, sizeof(float));

            // Derp, this was only TOH apparently!?
            //point_flags = compressed_fill<uint32_t>(stream_, true, true);

            stream_.read((char *)&u_float_2, sizeof(float));
            stream_.read((char *)&u_float_3, sizeof(float));
            
            min_pos = ace::vector3<float>(stream_);
            max_pos = ace::vector3<float>(stream_);
            autocenter_pos = ace::vector3<float>(stream_);

            stream_.read((char *)&sphere, sizeof(float));

            // Texture strings
            stream_.read((char *)&temp_count, sizeof(uint32_t));
            for (int x = 0; x < temp_count; x++) {
                std::string temp;

                READ_STRING(temp);
                textures.push_back(temp);
                LOG(DEBUG) << "Found texture: " << temp << " pos: " << stream_.tellg();
            }
            
            //Materials
            stream_.read((char *)&temp_count, sizeof(uint32_t));
            for (int x = 0; x < temp_count; x++) {
                 materials.push_back(material(stream_));
            }

            // Edges
            stream_.read((char *)&temp_count, sizeof(uint32_t));
            for (int x = 0; x < temp_count; x++) {
                
            }
        }

        lod_info::~lod_info() {}

        stage_texture::stage_texture() : file(""), filter(0), transform_id(0) { }
        stage_texture::stage_texture(std::fstream &stream_, uint32_t type_) {
            stream_.read((char *)&filter, sizeof(uint32_t));
            READ_STRING(file);
            stream_.read((char *)&transform_id, sizeof(uint32_t));
            if (type_ == 11) {
                READ_BOOL(wtf);
            }
        }

        material::material() { }
        material::material(std::fstream &stream_) {
            uint32_t textures_count, transforms_count;

            READ_STRING(name);

            stream_.read((char *)&type, sizeof(uint32_t));

            stream_.read((char *)&emissive, sizeof(float) * 4);
            stream_.read((char *)&ambient, sizeof(float) * 4);
            stream_.read((char *)&diffuse, sizeof(float) * 4);
            stream_.read((char *)&forced_diffuse, sizeof(float) * 4);
            stream_.read((char *)&specular, sizeof(float) * 4);
            stream_.read((char *)&specular_2, sizeof(float) * 4);
            
            stream_.read((char *)&specular_power, sizeof(float));
            stream_.read((char *)&pixel_shader, sizeof(uint32_t));
            stream_.read((char *)&vertex_shader, sizeof(uint32_t));
            stream_.read((char *)&u_long_1, sizeof(uint32_t));
            stream_.read((char *)&an_index, sizeof(uint32_t));
            stream_.read((char *)&u_long_2, sizeof(uint32_t));

            READ_STRING(surface);

            stream_.read((char *)&u_long_3, sizeof(uint32_t));
            stream_.read((char *)&render_flags, sizeof(uint32_t));

            stream_.read((char *)&textures_count, sizeof(uint32_t));
            stream_.read((char *)&transforms_count, sizeof(uint32_t));

            for (int x = 0; x < textures_count; x++) {
                texture_stages.push_back(stage_texture(stream_, type));
            }

            for (int x = 0; x < textures_count; x++) {
                uint32_t uv_source;
                stream_.read((char *)&uv_source, sizeof(uint32_t));
                transform_stages.push_back(std::pair<uint32_t, transform_matrix>(uv_source, transform_matrix(stream_)));
            }
            if (type >= 10) {
                texture_stages.push_back(stage_texture(stream_, type));
            }
        }

        proxy::proxy() { }
        proxy::proxy(std::fstream &stream_) {
            READ_STRING(name);
            transform = ace::transform_matrix(stream_);
            stream_.read((char *)&sequence_id, sizeof(uint32_t));
            stream_.read((char *)&named_selection_id, sizeof(uint32_t));
            stream_.read((char *)&bone_id, sizeof(uint32_t));
            stream_.read((char *)&section_id, sizeof(uint32_t));

        }
    }
}