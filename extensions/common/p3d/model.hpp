#pragma once

#include "ace_common.h"

#include "model_info.hpp"

namespace ace {
    namespace p3d {
        class model {
        public:
            model();
            ~model();

            model_info      info;

        };
    };
};