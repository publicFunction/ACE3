#define DEBUG_MODE_FULL
#include "script_component.hpp"

#define ACE_BASE_BULLET_LENGTH 32.893
#define __PROJECTILE_CLASS configFile >> "CfgAmmo" >> (_ammo select 4)

private["_impactSurfaceType", "_isDirectHit"];
private["_penetrationOrthogonalDepth", "_penetrationAngleDepth", "_penetrationCosAngle", "_projectileCaliber", "_projectileDensity", "_projectileLength", "_armorDensity"];
EXPLODE_9_PVT((_this select 0),_unit,_shooter,_projectile,_impactPosition,_projectileVelocity,_selection,_ammo,_surfaceDirection,_radius);
_impactSurfaceType = (_this select 0) select 9;
_isDirectHit = (_this select 0) select 10;
TRACE_2("",_impactSurfaceType,_isDirectHit);

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

_projectileDensity = getNumber (__PROJECTILE_CLASS >> "ace_penetration_density");
_projectileLength = (getNumber (__PROJECTILE_CLASS >> "ACE_bulletLength") ) / 0.039370; // fucking inches dafuq!?!?!?
_projectileCaliber = getNumber (__PROJECTILE_CLASS >> "caliber");

// If there was no ACE length defined, default to caliber
if(_projectileLength == 0) then {
    _projectileLength = ACE_BASE_BULLET_LENGTH * _projectileCaliber; // Length in mm, 1 caliber = 55.6 = ~13mm length round
};

// Small arms bullet penetration
//if((_ammo select 4) isKindOf "BulletBase") then {
    TRACE_3("Beginning bullet penetration", (_ammo select 4), _armorThickness, _armorDensity);
    
    _penetrationOrthogonalDepth = _projectileLength * (_projectileDensity / _armorDensity);
    _penetrationOrthogonalDepth = _penetrationOrthogonalDepth * ( (vectorMagnitude _projectileVelocity) / 1000);
    TRACE_5("ortho", _penetrationOrthogonalDepth, _projectileLength, _projectileDensity, _armorDensity,  (vectorMagnitude _projectileVelocity));

    // Calculate the angle only if our penetration depth is at least half the material thickness
    // Half is a perfect angular shot, any lower wont make it through
    //if( _penetrationOrthogonalDepth < _armorThickness * 0.5) exitWith { false };

    // Now calculate actual penetration depth based on angle
    _penetrationCosAngle = ( (vectorNormalized _surfaceDirection) vectorDotProduct ( vectorNormalized _projectileVelocity ) );
    _penetrationAngleDepth = abs (_penetrationOrthogonalDepth *  _penetrationCosAngle);
    TRACE_3("angle", _penetrationAngleDepth, _armorThickness, _penetrationCosAngle);
//};