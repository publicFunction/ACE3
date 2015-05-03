#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "simulation/object.hpp"

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
            vehicle(uint32_t id, ace::simulation::object_p object_);
            ~vehicle();

            std::vector<ace::vector3<float>> selection_position(const uint32_t lod, const std::string &name, const SELECTION_SEARCH_TYPE);

            std::vector<ace::vector3<float>> selection_by_name_vertices(const uint32_t lod, const std::string &);
            ace::simulation::named_selection_p selection_by_name(const uint32_t lod, const std::string &);

            std::shared_ptr<btTriangleMesh>                  bt_mesh;
            std::shared_ptr<btBvhTriangleMeshShape>          bt_shape;
            std::shared_ptr<btCollisionObject>               bt_object;

            ace::simulation::object_p        object;
        protected:
            
        };
    }
}