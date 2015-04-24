#include "p3d/model_info.hpp"

#define READ_DATA(output, size)  stream_.read((char *)&output, size);

namespace ace {
    namespace p3d {
        model_info::model_info() :
            lod_resolutions(nullptr), u_floats_1(nullptr), default_indicators(nullptr)
        { }

        model_info::model_info(std::fstream & stream_, const uint32_t lod_count) {
            model_info();

            lod_resolutions = new float[lod_count];
            READ_DATA(lod_resolutions, sizeof(float) * lod_count);

            READ_DATA(index, sizeof(uint32_t));
            READ_DATA(lod_sphere_mem, sizeof(float));
            READ_DATA(lod_sphere_geo, sizeof(float));
            READ_DATA(point_flags, sizeof(uint32_t) * 3);

            offset_1 = ace::vector3<float>(stream_);

            READ_DATA(map_icon_color, sizeof(uint32_t));
            READ_DATA(map_selected_color, sizeof(uint32_t));
            READ_DATA(view_density, sizeof(float));

            bbox_min_pos = ace::vector3<float>(stream_);
            bbox_max_pos = ace::vector3<float>(stream_);

            center_of_gravity = ace::vector3<float>(stream_);
            offset_2 = ace::vector3<float>(stream_);
            cog_offset = ace::vector3<float>(stream_);

            mass_vectors[0] = ace::vector3<float>(stream_);
            mass_vectors[1] = ace::vector3<float>(stream_);
            mass_vectors[2] = ace::vector3<float>(stream_);

            READ_DATA(thermal_profile_2, sizeof(uint8_t) * 24);

            READ_DATA(autocenter, sizeof(uint8_t));
            READ_DATA(lock_autocenter, sizeof(uint8_t));
            READ_DATA(allow_occlude, sizeof(uint8_t));
            READ_DATA(allow_occluded, sizeof(uint8_t));
            READ_DATA(allow_animation, sizeof(uint8_t));

            READ_DATA(u_bytes_1, sizeof(uint8_t) * 6);
            READ_DATA(thermal_profile, sizeof(uint8_t) * 24);
            READ_DATA(u_long_1, sizeof(uint32_t));

            skeleton = ace::p3d::skeleton(stream_, lod_count);
        }

        model_info::~model_info() {
            if (lod_resolutions)
                delete lod_resolutions;
            if (u_floats_1)
                delete u_floats_1;
            if (default_indicators)
                delete default_indicators;
        }
    }
}
