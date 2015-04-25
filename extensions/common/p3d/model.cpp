#include "p3d/model.hpp"

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {
        model::model() : skeleton(nullptr), info(nullptr), useFaceDefaults(nullptr) {}
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
            info = new model_info(stream_, lod_count);
            skeleton = &info->skeleton;

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
            uint32_t bone_count, local_lod_count;
            stream_.read((char *)&local_lod_count, sizeof(uint32_t));
            for (int lod = 0; lod < local_lod_count; lod++) {
                stream_.read((char *)&bone_count, sizeof(uint32_t));
                std::vector<uint32_t> lod_bone2anim;
                for (int x = 0; x < bone_count; x++) {
                    uint32_t anim_count;
                    stream_.read((char *)&anim_count, sizeof(uint32_t));

                    for (int anim = 0; anim < anim_count; anim++) {
                        uint32_t anim_index;
                        stream_.read((char *)&anim_index, sizeof(uint32_t));
                        skeleton->all_bones[x].animations.push_back(anim_index);
                    };
                }
            }

            // Anims2Bones
            for (int lod = 0; lod < lod_count; lod++) {
                for (animation & anim : animations) {
                    animate_bone next;
                    next.lod = lod;
                    stream_.read((char *)&next.index, sizeof(int32_t));
                    if (next.index != -1 && anim.type != 8 && anim.type != 9) {
                        next.axis_position = ace::vector3<float>(stream_);
                        next.axis_direction = ace::vector3<float>(stream_);
                    }
                    anim.bones.push_back(next);
                }
            }

            // LOD indexes
            for (int lod = 0; lod < lod_count; lod++) {
                uint32_t offset;
                stream_.read((char *)&offset, sizeof(uint32_t));
                start_lod.push_back(offset);
                LOG(DEBUG) << "LOD Offset: #" << lod << " : " << offset;
            }
            for (int lod = 0; lod < lod_count; lod++) {
                uint32_t offset;
                stream_.read((char *)&offset, sizeof(uint32_t));
                end_lod.push_back(offset);
                LOG(DEBUG) << "LOD Offset: #" << lod << " : " << offset;
            }

            // Attempt to read the faces?
            useFaceDefaults = new bool[lod_count];
            for (int lod = 0; lod < lod_count; lod++) {
                READ_BOOL(useFaceDefaults[lod]);
            }
            for (int x = 0; x < lod_count; x++) {
                if (!useFaceDefaults[x]) {
                    face_settings tface(stream_);
                }
            }
            
            
            for (int lod = 0; lod < lod_count; lod++) {
                printf("Endian? really? - %08x : %08x\n", (*info->lod_resolutions + lod), LODTYPE_FIRE_GEOMETRY);
                if ((*info->lod_resolutions+lod) == LODTYPE_FIRE_GEOMETRY) { //0x59c6f3b4    
                    lods.push_back(lod_info(stream_, lod));
                }
            }
            // READING THE ACTUAL LOD OMG
            
            //    stream_.seekg(start_lod[lod], stream_.beg);
            //    LOG(DEBUG) << "Parsing LOD: " << lod << " : " << stream_.tellg();
            //    
            //}
        }
        model::~model() {
            if(useFaceDefaults)
                delete[] useFaceDefaults;
            if (info)
                delete[] info;
        }
    }
}
