#pragma once

#include "ace_common.h"
#include "model.hpp"


namespace ace {
    namespace p3d {
        class parser {
        public:
            parser();
            ~parser();

            int ExpandUnknownInputLength(const char *in, char *OutBuf, long outlen);
            uint64_t swapLong(void *X);

            model * load(const std::string);
        };
    };
};