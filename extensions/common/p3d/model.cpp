#include "p3d/model.hpp"

#include "read_helpers.hpp"

namespace ace {
    namespace p3d {
        model::model() : skeleton(nullptr) {}
        model::model(std::fstream &stream_) {
            model();

            // get the full file size
            stream_.seekg(0, std::ios::end);
            size = stream_.tellg();
            stream_.seekg(0, std::ios::beg);

            // Parse header here
            READ_DATA(filetype, sizeof(uint32_t));
            READ_DATA(version, sizeof(uint64_t));
            if (version >= 48) {
                READ_STRING(prefix_name);
            }

            READ_DATA(lod_count, sizeof(uint32_t));

            // parse model info here
            info = model_info(stream_, lod_count);
            skeleton = &info.skeleton;

            // Read ahead because i dunno
            while (true) {
                char byte;
                stream_.read(&byte, 1);
                if (byte != -1) {
                    stream_.seekg(-1, stream_.cur);
                    break;
                };
            }



        }
        model::~model() {}
    }
}
