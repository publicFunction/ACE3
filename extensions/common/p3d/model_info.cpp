#include "p3d/model_info.hpp"

#include "read_helpers.hpp"

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

            READ_BOOL(autocenter);
            READ_BOOL(lock_autocenter);
            READ_BOOL(allow_occlude);
            READ_BOOL(allow_occluded);
            READ_BOOL(allow_animation);

            READ_DATA(u_bytes_1, sizeof(uint8_t) * 6);
            READ_DATA(thermal_profile, sizeof(uint8_t) * 24);
            READ_DATA(u_long_1, sizeof(uint32_t));

            // Parse the full skeletal structure
            skeleton = ace::p3d::skeleton(stream_, lod_count);

            READ_DATA(u_floats_1_size, sizeof(uint32_t));
            u_floats_1 = new float[u_floats_1_size];
            READ_COMPRESSED_DATA(u_floats_1, u_floats_1_size);

            READ_DATA(mass, sizeof(float));
            READ_DATA(mass_reciprocal, sizeof(float));
            READ_DATA(mass_alt, sizeof(float));
            READ_DATA(mass_alt_reciprocoal, sizeof(float));

            READ_DATA(u_bytes_1, sizeof(uint8_t) * 14);
            READ_DATA(u_short_1, sizeof(uint16_t));
            READ_DATA(u_long_1, sizeof(uint32_t));
            READ_BOOL(u_bool_1);
            READ_BOOL(u_bool_2);

            // skip a byte
            stream_.seekg(1, stream_.cur);

            //for (int x = 0; x < sizeof(_model->header.lod_count); x++) {
            //    READ_DATA(ifstream, _model->info.DefaultIndicators[x], sizeof(uint8_t) * 12);
            //}
            stream_.seekg(lod_count * 12, stream_.cur);
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
