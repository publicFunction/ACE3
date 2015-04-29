#include "controller.hpp"

namespace ace {
    namespace vehicledamage {
        controller::controller() { }
        controller::~controller() { }

        bool controller::handle_hit(const std::vector<std::string> & arguments, const std::string & result) {
            return false;
        }
    }
}

