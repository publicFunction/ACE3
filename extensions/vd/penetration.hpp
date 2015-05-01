#pragma once

#include "shared.hpp"
#include "vector.hpp"

namespace ace {
    namespace vehicledamage {

        class projectile {
        public:
            projectile(uint32_t type_id, const std::string & classname, float length, float diameter, float density, 
                ace::vector3<float> vel, ace::vector3<float> pos, ace::vector3<float> dir) : 
                _type(type_id), _classname(classname), _length(length), _diameter(diameter), _density(density),
                _velocity(vel), _position(pos), _direction(dir)
            {}

            projectile & operator= (const projectile& other) { 
                _type = other._type; _classname = other._classname; _length = other._length; _diameter = other._diameter, _density = other._density;
                _velocity = other._velocity; _position = other._position; _direction = other._direction;
                return *this; 
            }

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
            game_hit(   uint32_t id, uint32_t object_id, 
                        const std::string & classname, const std::string & selection, 
                        projectile proj, 
                        float ortho_surface, ace::vector3<float> impact_pos, ace::vector3<float> impact_vel) 
            : _id(id), _object_id(object_id), 
            _classname(classname), _selection(selection), 
            _projectile(proj), 
            _orthogonal_surface(ortho_surface), _impact_position(impact_pos), _impact_velocity(impact_vel)
            {}
            
            static game_hit_p create(const arguments & _args) {
                return std::make_shared<game_hit>(-1, _args.as_uint32(0), _args.as_string(1), _args.as_string(2),
                    projectile(_args.as_uint32(3), _args.as_string(4), _args.as_float(5), _args.as_float(6), _args.as_float(7),
                    _args.as_vector(8), _args.as_vector(9), _args.as_vector(10)),
                    _args.as_float(11), _args.as_vector(12), _args.as_vector(13));
            }

            uint32_t            _id;
            uint32_t            _object_id;
            
            std::string         _classname;
            std::string         _selection;

            projectile          _projectile;

            float               _orthogonal_surface;
            ace::vector3<float> _impact_position;
            ace::vector3<float> _impact_velocity;
        };
        typedef std::shared_ptr<game_hit> game_hit_p;

        class base_penetration_model {

        };

        class penetration_model : public base_penetration_model {
        public:
        };
    }
}