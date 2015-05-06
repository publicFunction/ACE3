#define COMPONENT vehicledamage
#include "\z\ace\addons\main\script_mod.hpp"

#ifdef DEBUG_ENABLED_VEHICLEDAMAGE
    #define DEBUG_MODE_FULL
#endif

#ifdef DEBUG_ENABLED_VEHICLEDAMAGE
    #define DEBUG_SETTINGS DEBUG_ENABLED_VEHICLEDAMAGE
#endif

#include "\z\ace\addons\main\script_macros.hpp"

#define CALL_EXT(x) "ace_vd" callExtension x