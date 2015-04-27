#pragma once

#include "ace_common.h"
#include "pbo/archive.hpp"

namespace ace { 
    namespace pbo {
        class search {
        public:
            search();

            const std::vector<std::string> & active_pbo_list() { return _active_pbo_list;  }
        protected:
            bool generate_pbo_list();

            std::vector<std::string> _active_pbo_list;
            std::vector<ace::pbo::archive_p> _archives;
        };
    }
}