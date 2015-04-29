#pragma once

#include "shared.hpp"
#include "vector.hpp"

namespace ace {
    namespace vehicledamage {

        class projectile {
        public:
            uint32_t            _type;          // bullet, longrod, shell, etc.
            
            std::string         _classname;

            float               _length;
            float               _diameter;
            float               _density;

            ace::vector3<float> _velocity;
            ace::vector3<float> _position;
            ace::vector3<float> _direction;
        };

        // This class tracks incoming hits from the engine
        class game_hit {
        public:
            uint32_t            _id;
            uint32_t            _object_id;
            
            std::string         _classname;
            std::string         _selection;

            projectile          _projectile;

            float               _orthogonal_surface;
            ace::vector3<float> _impact_location;
            ace::vector3<float> _impact_velocity;
        };

        class base_penetration_model {

        };

        class penetration_model : public base_penetration_model {
        public:
        };
    }
}