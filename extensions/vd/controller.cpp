#include "controller.hpp"

namespace ace {
    namespace vehicledamage {
        controller::controller() { }
        controller::~controller() { }

        /*
            This is sent in via SQF by a callExtension call, with the variables:
            
           object_id,
            classname;selection,projectile_classname;projectile_density,
            projectile_length;projectile_diameter;projectile_velocity;projectile_position;projectile_direction,
            orthogonal_surface;impact_location;impact_velocity

           These are treed with 2 delims to make this extensible and back-compat. One is , between actual parameters, and then ; between sub-parameters

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
        */
        bool controller::handle_hit(const std::vector<std::string> & arguments, const std::string & result) {
            
            if (arguments.size() < 15) return false;
            for (auto & item : arguments) {
                // parse out the hitpart sent in
            }

            return false;
        }
    }
}

