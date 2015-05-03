#include "script_component.hpp"
PARAMS_1(_vehicle);
private["_id", "_model"];

if(!GVAR(Enabled)) exitWith {};

_id = GVAR(vehicle_id);
GVAR(vehicle_id) = _id + 1;
_model = (configFile >> "CfgVehicles" >> (typeOf _vehicle) >> "model"); 

CALL_EXT format["register_vehicle:%1,%2",_model,_id];
_vehicle setVariable[GVAR(id), _id, false];
