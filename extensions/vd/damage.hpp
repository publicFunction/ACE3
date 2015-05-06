#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "game.hpp"
#include "vehicle.hpp"
#include "penetration.hpp"

namespace ace {
    namespace vehicledamage {
        namespace damage {
            class damage_result {
            public:
                bool            placeholder_1;
                float            linear_depth;
            };

            class base_damage_model {
            public:
                base_damage_model(const gamehit &hit_, vehicle_p &vehicle_, penetration::penetration_result penetration_) : _hit(hit_), _vehicle(vehicle_), _penetration(penetration_) {
                    process();
                }
                virtual bool                        process() = 0;
                virtual const damage_result            & result() { return _result; }

                virtual bool                        complete() { return _complete; }
            protected:
                gamehit                                    _hit;
                vehicle_p                                _vehicle;
                penetration::penetration_result            _penetration;
                damage_result                            _result;

                volatile bool                            _complete;
            };
        }
    }
}