#pragma once

#include "ace_common.h"
#include "pbo/search.hpp"
#include "p3d/model.hpp"
#include <thread>

namespace ace {
    class model_entry {
    public:
        model_entry(const std::string & p3d_path_, ace::p3d::model_p model_) : p3d_path(p3d_path_), model(model_) {  }
        std::string         p3d_path;
        ace::p3d::model_p   model;
    };

    class model_collection {
    public:
        model_collection();
        bool load_model(const std::string & p3d_path);
   
        bool init();
        bool reset();
        
        static model_collection& get() {
            static model_collection instance;
            return instance;
        }

        std::vector<model_entry> models;

        bool initialized(void) const { return _initialized; }
        bool ready(void) const { return _ready; }
    protected:
        bool _load_model(const std::string &, const std::string &);

        volatile bool _ready;
        volatile bool _initialized;

        ace::pbo::search_p _pbo_searcher;

        std::thread _loadWorker;
    };
}