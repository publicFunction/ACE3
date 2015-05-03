#pragma once

#include "shared.hpp"
#include "singleton.hpp"
#include "penetration.hpp"
#include "arguments.hpp"
#include "dispatch.hpp"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

namespace ace {
    namespace vehicledamage {
        class controller 
            : public singleton<controller>,
            public dispatcher {
        public:
            controller();
            ~controller();

            bool handle_hit(const arguments & args, const std::string & result);
#ifdef _DEBUG
            bool _test_raycast(const arguments & args, const std::string & result);
            bool _test_selection(const arguments & args, const std::string & result);
#endif
            // Bullet physx world
            std::shared_ptr<btDefaultCollisionConfiguration>    bt_collisionConfiguration;
            std::shared_ptr<btCollisionDispatcher>              bt_collisionDispatcher;
            std::shared_ptr<btCollisionWorld>                   bt_world;
        };

    }
}

