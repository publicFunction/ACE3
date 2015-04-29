#pragma once

#include "shared.hpp"
#include "singleton.hpp"
#include "penetration.hpp"
#include "arguments.hpp"

namespace ace {
    namespace vehicledamage {
        class controller 
            : public singleton<controller> {
        public:
            controller();
            ~controller();

            bool handle_hit(const arguments & args, const std::string & result);
        };

    }
}

