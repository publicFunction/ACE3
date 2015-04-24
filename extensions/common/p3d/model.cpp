#include "p3d/model.hpp"

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {
        model::model() : skeleton(nullptr) {}
        model::model(std::fstream &stream_, const std::string &filename_) {
            filename = filename_;

            // get the full file size
            stream_.seekg(0, std::ios::end);
            size = stream_.tellg();
            stream_.seekg(0, std::ios::beg);

            // Parse header here
            stream_.read((char *)&filetype, sizeof(uint32_t));
            stream_.read((char *)&version, sizeof(uint64_t));
            if (version >= 48) {
                READ_STRING(prefix_name);
            }

            stream_.read((char *)&lod_count, sizeof(uint32_t));

            // parse model info here
            info = model_info(stream_, lod_count);
            skeleton = &info.skeleton;

            /*while (true) {
                char byte;
                stream_.read(&byte, 1);
                if (byte != -1) {
                    stream_.seekg(-1, stream_.cur);
                    break;
                };
            }*/
            
            READ_BOOL(has_animations);
            if (has_animations) {
                uint32_t animation_count = 0;
                stream_.read((char *)&animation_count, sizeof(uint32_t));
                for (int x = 0; x < animation_count; x++) {
                    animations.push_back(animation(stream_));
                }
            }

            // Now we re-walk, and association animations and bones
            uint32_t bone_count;
            stream_.read((char *)&bone_count, 4);

            for (int lod = 0; lod < lod_count; lod++) {
                std::vector<uint32_t> lod_bone2anim;
                for (int x = 0; x < bone_count; x++) {
                    uint32_t anim_count;
                    stream_.read((char *)&anim_count, 4);

                    for (int anim = 0; anim < anim_count; anim++) {
                        uint32_t anim_index;
                        stream_.read((char *)&anim_index, 4);
                        lod_bone2anim.push_back(anim_index);
                    };
                }
                bones2anims.push_back(lod_bone2anim);
            }

            // Anims2Bones
            for (int lod = 0; lod < lod_count; lod++) {
                for (animation & anim : animations) {
                    animate_bone next;
                    next.lod = lod;
                    stream_.read((char *)&next.index, 4);
                    if (next.index != -1) {
                        next.axis_position = ace::vector3<float>(stream_);
                        next.axis_direction = ace::vector3<float>(stream_);
                    }
                    anim.bones.push_back(next);
                }
            }
            LOG(DEBUG) << "LOD offsets start at " << stream_.tellg();
            // LOD indexes
            for (int lod = 0; lod < lod_count; lod++) {
                uint32_t offset;
                stream_.read((char *)&offset, 4);
                start_lod.push_back(offset);
                LOG(DEBUG) << "LOD Offset: #" << lod << " : " << offset;
            }
            for (int lod = 0; lod < lod_count; lod++) {
                uint32_t offset;
                stream_.read((char *)&offset, 4);
                end_lod.push_back(offset);
                LOG(DEBUG) << "LOD Offset: #" << lod << " : " << offset;
            }
        }
        model::~model() {}
    }
}
