#pragma once

#include "shared.hpp"
#include "vector.hpp"
#include "simulation/object.hpp"


namespace ace {
    namespace vehicledamage {

        enum SELECTION_SEARCH_TYPE {
            AVERAGE_CENTER, POINTS, FACES
        };

        class base_vehicle {};

        class vehicle : public base_vehicle {
        public:
            vehicle(ace::simulation::object_p object_);

            std::vector<ace::vector3<float>> selection_position(const uint32_t lod, const std::string &name, const SELECTION_SEARCH_TYPE);
            ace::simulation::named_selection_p selection_by_name(const uint32_t lod, const std::string &);

            ace::simulation::object_p        object;
        protected:
            
        };
    }
}