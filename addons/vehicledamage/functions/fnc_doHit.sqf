#define DEBUG_MODE_FULL
#include "script_component.hpp"

#define ACE_BASE_BULLET_LENGTH 32.893
#define __VEHICLE_CLASS configFile >> "CfgVehicles" >> (typeOf _unit)
#define __PROJECTILE_CLASS configFile >> "CfgAmmo" >> (_ammo select 4)

private["_impactSurfaceType", "_isDirectHit", "_command", "_model"];
private["_penetrationOrthogonalDepth", "_penetrationAngleDepth", "_penetrationCosAngle", "_projectileCaliber", "_projectileDensity", "_projectileLength", "_armorDensity"];
EXPLODE_9_PVT((_this select 0),_unit,_shooter,_projectile,_impactPosition,_projectileVelocity,_selection,_ammo,_surfaceDirection,_radius);
_impactSurfaceType = (_this select 0) select 9;
_isDirectHit = (_this select 0) select 10;
TRACE_2("",_impactSurfaceType,_isDirectHit);

/*
_penetrationData = [_impactSurfaceType] call FUNC(getPenetrationData);
TRACE_1("", _penetrationData);
if(isNil "_penetrationData") exitWith {
    diag_log text format["[ACE] - ERROR - ace_vehicledamage: Invalid penetration surface"];
    false
};

// @TODO: Skip surface thickness discovery, use armor thickness for now
if( (_penetrationData select 0) <= 0) exitWith { 
    diag_log text format["[ACE] - @TODO variable thickness surfaces are not yet supported"];
    false
};

// Skip it if the surface cant be penetrated
if( (_penetrationData select 4) <= 0 && {(_penetrationData select 5) <= 0}) exitWith { 
    diag_log text format["[ACE] - Superman surface"];
    false 
};

// Determine the actual penetration through density first, 
// then check thickness to see if we can go far enough
// 8600 is our base density for steel, 11500 for lead
_armorDensity = _penetrationData select 1;
_armorThickness = _penetrationData select 0;

*/
_projectileDensity = getNumber (__PROJECTILE_CLASS >> "ACE_bulletDensity");
_projectileLength = (getNumber (__PROJECTILE_CLASS >> "ACE_bulletLength") ) / 0.039370; // fucking inches dafuq!?!?!?
_projectileDiameter = (getNumber (__PROJECTILE_CLASS >> "ACE_caliber") ) / 0.039370;  // fucking inches dafuq!?!?!?
_projectileCaliber = getNumber (__PROJECTILE_CLASS >> "caliber");

TRACE_4("Measurements", _projectileDensity,_projectileLength,_projectileDiameter,_projectileCaliber);

// If there was no ACE length defined, default to caliber
if(_projectileLength == 0) then {
    _projectileLength = ACE_BASE_BULLET_LENGTH * _projectileCaliber; // Length in mm, 1 caliber = 55.6 = ~13mm length round
};
/*
object_id,
        classname, selection, projectile_classname, projectile_density,
        projectile_length, projectile_diameter, projectile_velocity, projectile_position, projectile_direction,
        orthogonal_surface, impact_location, impact_velocity
*/

#define VECTOR_TEXT(x) ([(x)] call FUNC(_textVector))
#define RELATIVE_VECTOR_TEXT(o,x) ([(o worldToModelVisual x)] call FUNC(_textVector))
FUNC(_textVector) = {
    private["_str"];
    _str = format["%1;%2;%3", ((_this select 0) select 0), ((_this select 0) select 1), ((_this select 0) select 2)];
    _str
};

_model = getText (__VEHICLE_CLASS >> "model");

_relativePosition = _unit worldToModelVisual _impactPosition;
_relativeVelocityAdjust = _impactPosition vectorAdd (_projectileVelocity vectorMultiply 10);
_relativeVelocity = _relativePosition vectorFromTo _relativeVelocityAdjust;

_command = format["hit:%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14", 
                        -1,  // vehicle id registered
                        _model, _selection, 
                        -1, //projectile type id
                        (_ammo select 4), _projectileLength, _projectileDiameter, _projectileDensity,
                            VECTOR_TEXT(_projectileVelocity), 
                            VECTOR_TEXT(getPosASL _projectile), 
                            VECTOR_TEXT(vectorDir _projectile), 
                            VECTOR_TEXT(_surfaceDirection), 
                            VECTOR_TEXT(_relativePosition),  
                            VECTOR_TEXT(_relativeVelocity)
                ];   
TRACE_1("", _command);                