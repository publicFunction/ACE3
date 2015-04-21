#define DEBUG_MODE_FULL
#include "script_component.hpp"

private["_surface", "_direct"];

EXPLODE_9_PVT((_this select 0),_unit,_shooter,_bullet,_position,_velocity,_selection,_ammo,_direction,_radius);
_surface = (_this select 0) select 9;
_direct = (_this select 0) select 10;
TRACE_2("",_surface,_direct);

_penetrationData = [_surface] call FUNC(getPenetrationData);
if(isNil "_penetrationData") exitWith {
    diag_log text format["[ACE] - ERROR - ace_vehicledamage: Invalid penetration surface"];
    false
};

// Skip it if the surface cant be penetrated
if( (_penetrationData select 4) <= 0) exitWith { false };

