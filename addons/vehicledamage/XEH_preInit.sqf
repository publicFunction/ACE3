#include "script_component.hpp"

ADDON = false;

PREP(registerDamageHandler);
PREP(registerWithExtension);

PREP(dispatchHitPart);
PREP(dispatchDamage);
PREP(doHit);

// Extension calling functionality
PREP(initializeExtension);

ADDON = true;