#include "script_component.hpp"

// Handle damage to local vehicles
[QGVAR(hp), FUNC(dispatchHitPart)] call EFUNC(common,addEventHandler);

