#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "arguments.hpp"
#include "materials.hpp"

namespace ace {
    namespace vehicledamage {

        enum class PROJECTILE_TYPE {
            CYLINDER = 1,
            FRUSTUM = 2,    // This is long rod, but working length changes
            MISSILE = 3,    // These will most likely be a hybrid of rod projected kenetic rounds
            BULLET = 4,     // Not used? Can we just use cylinder long rod equations?
            FRAGMENT = 5
        };

        class projectile {
        public:
            projectile(uint32_t projtypeid_, const std::string & classname_, float length_, float diameter_, float density_, float frustum_length_, float frustum_diameter_,
                ace::vector3<float> vel, ace::vector3<float> pos, ace::vector3<float> dir) :
                type(PROJECTILE_TYPE(projtypeid_)), classname(classname_), length(length_), diameter(diameter_), density(density_), frustum_length(frustum_length_), frustum_diameter(frustum_diameter_),
                velocity(vel), position(pos), direction(dir)
            {}

            projectile & operator= (const projectile& other) {
                type = other.type; classname = other.classname; length = other.length; diameter = other.diameter, density = other.density; 
                frustum_length = other.frustum_length; frustum_diameter = other.frustum_diameter;
                velocity = other.velocity; position = other.position; direction = other.direction;
                return *this;
            }

            PROJECTILE_TYPE     type;          // bullet, longrod, shell, etc.

            std::string         classname;

            float               length;
            float               diameter;
            float               density;

            float               frustum_diameter;
            float               frustum_length;

            std::unordered_map<std::string, float> extended;

            ace::vector3<float> velocity;
            ace::vector3<float> position;
            ace::vector3<float> direction;
        };

        // This class tracks incoming hits from the engine
        class gamehit {
        public:
            gamehit(uint32_t id, uint32_t objectid,
                const std::string & classname, const std::string & selection,
                projectile proj,
                ace::vector3<float> orthosurface, ace::vector3<float> impactpos, ace::vector3<float> impactvel)
                : id(id), objectid(objectid),
                classname(classname), selection(selection),
                projectile(proj),
                surface(orthosurface), impactposition(impactpos), impactvelocity(impactvel)
            {}

            static std::shared_ptr<gamehit> create(const arguments & args) {
                return std::make_shared<gamehit>(-1, args.as_uint32(0), args.as_string(1), args.as_string(2),
                    ace::vehicledamage::projectile(args.as_uint32(3), args.as_string(4), args.as_float(5), args.as_float(6), args[7], args[8], args[9],
                    args.as_vector(10), args[11], args.as_vector(12)),
                    args.as_vector(13), args.as_vector(14), args.as_vector(15));
            }
            
            uint32_t            id;
            uint32_t            objectid;

            std::string         classname;
            std::string         selection;

            projectile          projectile;

            ace::vector3<float> surface;

            ace::vector3<float> impactposition;
            ace::vector3<float> impactvelocity;
        };
        typedef std::shared_ptr<gamehit> gamehit_p;
    }
}