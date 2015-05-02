#include "script_component.hpp"

ADDON = false;

PREP(registerVehicleDamageHandler);
PREP(registerVehicleWithExtension);

PREP(dispatchHitPart);
PREP(dispatchDamage);
PREP(doHit);

// Extension calling functionality
PREP(initializeExtension);

// Unique local vehicle ID
GVAR(vehicle_id) = 0;

ADDON = true;