#include "script_component.hpp"

PREP(callSync);
PREP(callAsync);        // Alias for AsyncBegin, waiting, and result
PREP(callAsyncBegin);
PREP(callSyncResult);

// check dlls
{
    if (_x callExtension "version" == "") then {
        private "_errorMsg";
        _errorMsg = format ["Extension %1.dll not installed.", _x];

        diag_log text format ["[ACE] ERROR: %1", _errorMsg];
        ["[ACE] ERROR", _errorMsg, {findDisplay 46 closeDisplay 0}] call EFUNC(common,errorMessage);
    };
} forEach ["ace_breakLine", "ace_advanced_ballistics", "ace_fcs"];