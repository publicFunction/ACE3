#define DEBUG_MODE_FULL
#include "script_component.hpp"
PARAMS_2(_args,_handle);
private["_result"];

_result = CALL_EXT("fetch_result:1");
while(_result != "") then {
    diag_log text format["result={%1}", _result];
    _result = CALL_EXT("fetch_result:1");
};