#include "model_collection.hpp"

namespace ace {
    model_collection::model_collection() : _ready(false) {
        // Finished preparing
        
        _ready = true;
    }

    bool model_collection::load_model(const std::string & model_name) {
       
        // Flag ourselves as unready, because we are loading a model
       _ready = false;



       return true;
    }
}