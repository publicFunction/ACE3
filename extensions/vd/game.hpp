#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "arguments.hpp"

namespace ace {
    namespace vehicledamage {

        class projectile {
        public:
            projectile(uint32_t projtypeid, const std::string & classname, float length, float diameter, float density,
                ace::vector3<float> vel, ace::vector3<float> pos, ace::vector3<float> dir) :
                type(projtypeid), classname(classname), length(length), diameter(diameter), density(density),
                velocity(vel), position(pos), direction(dir)
            {}

            projectile & operator= (const projectile& other) {
                type = other.type; classname = other.classname; length = other.length; diameter = other.diameter, density = other.density;
                velocity = other.velocity; position = other.position; direction = other.direction;
                return *this;
            }

            uint32_t            type;          // bullet, longrod, shell, etc.

            std::string         classname;

            float               length;
            float               diameter;
            float               density;

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
                float orthosurface, ace::vector3<float> impactpos, ace::vector3<float> impactvel)
                : id(id), objectid(objectid),
                classname(classname), selection(selection),
                projectile(proj),
                orthogonalsurface(orthosurface), impactposition(impactpos), impactvelocity(impactvel)
            {}

            static std::shared_ptr<gamehit> create(const arguments & args) {
                return std::make_shared<gamehit>(-1, args.as_uint32(0), args.as_string(1), args.as_string(2),
                    ace::vehicledamage::projectile(args.as_uint32(3), args.as_string(4), args.as_float(5), args.as_float(6), args.as_float(7),
                    args.as_vector(8), args.as_vector(9), args.as_vector(10)),
                    args.as_float(11), args.as_vector(12), args.as_vector(13));
            }

            uint32_t            id;
            uint32_t            objectid;

            std::string         classname;
            std::string         selection;

            projectile          projectile;

            float               orthogonalsurface;
            ace::vector3<float> impactposition;
            ace::vector3<float> impactvelocity;
        };
        typedef std::shared_ptr<gamehit> gamehit_p;
    }
}