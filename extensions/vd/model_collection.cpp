#include "model_collection.hpp"
#include "membuf.hpp"

namespace ace {
    model_collection::model_collection() : _ready(false), _initialized(false) { }

    bool model_collection::init(void) {
        if (_initialized) return true;
       
        _pbo_searcher = std::make_shared<ace::pbo::search>();

        _initialized = true;
        _ready = true;

        return true;
    }
    bool model_collection::reset(void) { 
    
        return true;
    }

    // Model loading implementation
    bool model_collection::_load_model(const std::string &p3d_path, const std::string &pbo_file) {
        std::ifstream _filestream;

        _ready = false;

        _filestream.open(pbo_file, std::ios::binary | std::ios::in);
        if (!_filestream.good()) {
            throw - 1;
        }

        // We know the model exists, and have the pbo and file path now.
        ace::pbo::archive _archive(_filestream);
        ace::pbo::file_p _file = std::make_shared<ace::pbo::file>();
   
        std::string search_filename = p3d_path;

        // Remove leading slash
        if (search_filename[0] == '\\') {
            search_filename.erase(0, 0);
        }

        search_filename.erase(search_filename.find(_archive.info->data), _archive.info->data.size()+1);
        for(auto & entry : _archive.entries) {
            if (entry->filename == search_filename) {
                // Do shit here
                if (_archive.get_file(_filestream, entry, _file)) {
                    ace::membuf _memory_buffer((char *)_file->data, _file->size);
                    std::istream _data_stream(&_memory_buffer);

                    ace::p3d::model_p _model = std::make_shared<ace::p3d::model>(_data_stream);
                    models.push_back(model_entry(p3d_path, _model));
                }
                break;
            }
        }

        _filestream.close();

        _ready = true;

        return true;
    }

    bool model_collection::load_model(const std::string & p3d_path) {
       
        // Flag ourselves as unready, because we are loading a model
        _ready = false;

        // Find the model in the file index
        for (auto & kv : _pbo_searcher->file_index()) {
            if (kv.first == p3d_path) {
                return _load_model(kv.first, kv.second);
                break;
            }
        }

        return false;
    }
}