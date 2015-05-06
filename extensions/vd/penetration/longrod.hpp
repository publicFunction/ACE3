#pragma once

#include "penetration.hpp"

namespace ace {
    namespace vehicledamage {
        namespace penetration {
            class longrod : public base_penetration_model {
            public:
                bool process() override;
            protected:
                float _working_length() {
                    return _hit.projectile.length;
                }

            private:
                const static float material_coefficients[][5];
            };
        }
    }
};