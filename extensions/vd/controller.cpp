#include "controller.hpp"

namespace ace {
    namespace vehicledamage {
        controller::controller() { }
        controller::~controller() { }

        /*
            This is sent in via SQF by a callExtension call, with the variables:
            
            // A vector is formatted in x;y;z

           object_id,
            classname,selection,projectile_classname,projectile_density,
            projectile_length,projectile_diameter,projectile_velocity,projectile_position,projectile_direction,
            orthogonal_surface,impact_location,impact_velocity

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
            //hit:-1,I_MBT_03_cannon_F,foobar,-1,big_projectile_wtf,123,456,789,1.0;2.0;3.0,4;5;6,7.0;8.0;9.0,-9.123,1.0;2.0;3.0,4;5;6
            game_hit_p _hit_ptr = std::make_shared<game_hit>(-1, _args[0].as_uint32(), _args[1].as_string(), _args[2].as_string(),
                projectile(_args[3].as_uint32(), _args[4].as_string(), _args[5].as_float(), _args[6].as_float(), _args[7].as_float(), 
                _args[8].as_vector(), _args[9].as_vector(), _args[10].as_vector()),
                _args[11].as_float(), _args[12].as_vector(), _args[13].as_vector());


            return false;
        }
    }
}

