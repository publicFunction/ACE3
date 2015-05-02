#include "script_component.hpp"
PARAMS_1(_vehicle);
private["_id", "_model"];

if(!GVAR(Enabled)) exitWith {};

_id = GVAR(vehicle_id);
_model = (configFile >> "CfgVehicles" >> (typeOf _vehicle) >> "model"); 

_vehicle setVariable[GVAR(id), _id, false];

CALL_EXT format["registerVehicle:%1,%2", _id, _model];

GVAR(vehicle_id) = _id + 1;