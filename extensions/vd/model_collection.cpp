#include "model_collection.hpp"

namespace ace {
    model_collection::model_collection() : _ready(false), _initialized(false) { }

    bool model_collection::init(void) {
        if (_initialized) return true;
       
        _pbo_searcher = std::make_shared<ace::pbo::search>();

        _initialized = true;
        return true;
    }
    bool model_collection::reset(void) { 
    
        return true;
    }

    bool model_collection::load_model(const std::string & p3d_path) {
       
        // Flag ourselves as unready, because we are loading a model
       _ready = false;

       // Find the model in the file index
       

       return true;
    }
}