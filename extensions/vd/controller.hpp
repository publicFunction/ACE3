#pragma once

#include "shared.hpp"
#include "singleton.hpp"

namespace ace {
    namespace vehicledamage {
        class controller 
            : public singleton<controller> {
        public:
            controller();
            ~controller();

            bool handle_hit(const std::vector<std::string> & arguments, const std::string & result);
        };

    }
}

