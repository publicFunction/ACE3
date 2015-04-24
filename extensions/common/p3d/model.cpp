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
            LOG(DEBUG) << "index2 !" << std::hex << stream_.tellg();
            READ_BOOL(has_animations);
            if (has_animations) {
                uint32_t animation_count = 0;
                stream_.read((char *)&animation_count, sizeof(uint32_t));
                for (int x = 0; x < animation_count; x++) {
                    animations.push_back(animation(stream_));
                }
            }

        }
        model::~model() {}
    }
}
