#pragma once

#include "ace_common.h"
#include "p3d/model.hpp"


namespace ace {
    namespace p3d {
        class parser {
        public:
            parser();
            ~parser();

            model * load(const std::string);
        };
    };
};