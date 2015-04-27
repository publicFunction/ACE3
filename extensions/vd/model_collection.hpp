#pragma once

#include "ace_common.h"
#include "pbo/search.hpp"
#include "p3d/model.hpp"
#include <thread>

namespace ace {
    class model_collection {
    public:
        model_collection();
        bool load_model(const std::string & model_name);
   
        bool init();
        bool reset();
        
        static model_collection& get() {
            static model_collection instance;
            return instance;
        }

        const bool initialized(void) { return _initialized; }
        const bool ready(void) { return _ready; }
    protected:
        volatile bool _ready;
        volatile bool _initialized;

        ace::pbo::search_p _pbo_searcher;

        std::thread _loadWorker;
    };
}