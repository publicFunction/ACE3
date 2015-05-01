#include "controller.hpp"

namespace ace {
    namespace vehicledamage {
        controller::controller() { }
        controller::~controller() { }

        /*
            This is sent in via SQF by a callExtension call, with the variables:
            
            // A vector is formatted in x;y;z

           object_id,
            classname, selection, projectile_classname, projectile_density,
            projectile_length, projectile_diameter, projectile_velocity, projectile_position, projectile_direction,
            orthogonal_surface, impact_location, impact_velocity

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
        bool controller::handle_hit(const arguments &_args, const std::string & result) {
            if (_args.size() < 13) return false;

            game_hit_p _hit = game_hit::create(_args);
            


            return false;
        }
    }
}

