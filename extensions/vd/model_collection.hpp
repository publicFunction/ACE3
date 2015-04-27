#pragma once

#include "ace_common.h"
#include <thread>

namespace ace {
    class model_collection {
    public:
        model_collection();
        bool load_model(const std::string & model_name);
   
        static model_collection& get() {
            static model_collection instance;
            return instance;
        }

        const bool ready(void) { return _ready; }
    protected:
        volatile bool _ready;

        std::thread _loadWorker;
    };
}