#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "vehicle.hpp"

namespace ace {
    namespace vehicledamage {
        class penetration_result {
        public:
            bool            placeholder;
        };
        
        class base_penetration_model {
        public:
            virtual bool                begin(const gamehit &, const vehicle &) = 0;
            virtual penetration_result  result() = 0;
        };

        class penetration_model : public base_penetration_model {
        public:
        };
    }
}