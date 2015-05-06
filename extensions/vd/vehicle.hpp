#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "simulation/object.hpp"

#define BT_NO_SIMD_OPERATOR_OVERLOADS
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/Gimpact/btGImpactShape.h"

namespace ace {
    namespace vehicledamage {

        enum SELECTION_SEARCH_TYPE {
            AVERAGE_CENTER, POINTS, FACES
        };

        class base_vehicle {};

        class vehicle : public base_vehicle {
        public:
            vehicle(uint32_t, ace::simulation::object_p, ace::vector3<float>);
            ~vehicle();

            float thickness(const ace::vector3<float> &, const ace::vector3<float> & );

            std::vector<ace::vector3<float>> selection_position(const uint32_t, const std::string &, const SELECTION_SEARCH_TYPE);
            std::vector<ace::vector3<float>> selection_by_name_vertices(const uint32_t, const std::string &);
            ace::simulation::named_selection_p selection_by_name(const uint32_t, const std::string &);

            // Bullet physx objects
            std::shared_ptr<btTriangleMesh>                  bt_mesh;
            std::shared_ptr<btBvhTriangleMeshShape>          bt_shape;
            std::shared_ptr<btCollisionObject>               bt_object;
            std::shared_ptr<btRigidBody>                     bt_body;

            ace::simulation::object_p        object;
        protected:
            
        };
        typedef std::shared_ptr<vehicle> vehicle_p;
    }
}