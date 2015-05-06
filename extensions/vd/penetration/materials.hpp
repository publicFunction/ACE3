#pragma once

namespace ace {
    namespace vehicledamage {

        enum MATERIAL_TYPES {
            TUNGSTEN = 0,
            DEPLETED_URANIUM = 1,
            STEEL = 2
        };

        // Hardness, density
        const static float material_properties[][2] = {
            { 600, 4800 },
            { 600, 4800 },
            { 300, 4800 }
        };
    }
}
