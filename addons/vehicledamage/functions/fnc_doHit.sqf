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
if((_ammo select 4) isKindOf "BulletBase") then {
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
};
#define __e 2.71828182845904523536028747135266249775724709369995 
#define tanh(x) ((__e^(2 *x)) - 1) / ((__e^(2 *x)) + 1) 


// Calculate shell based penetrator solutions, this assumed a shaped APDFS round
if((_ammo select 4) isKindOf "BulletBase") then {
    private["_materialCoefficients"];
    _material = _this select 0;
    
    _b0 = 0.283;
    _b1 = 0.0656;
    _m = -0.224;
    
    _materialCoefficients = HASH_CREATE;
    HASH_SET(_materialCoefficients, "tu", [0.994, 134.5, -0.148, 0, 0] ];
    HASH_SET(_materialCoefficients, "du", [0.825, 90.0, -0.0849, 0, 0] ];
    HASH_SET(_materialCoefficients, "steel", [1.104, 9874, 0, 0.3598, -0.2342] ];
    
    _a = HASH_GET(_materialCoefficients, _material) select 0;
    _c0 = HASH_GET(_materialCoefficients, _material) select 1;
    _c1 = HASH_GET(_materialCoefficients, _material) select 2;
    _k = HASH_GET(_materialCoefficients, _material) select 3;
    _n = HASH_GET(_materialCoefficients, _material) select 4;
    
    _s2 = 0;
    _projectileHardness = 3000;
    _targetHardness = 300;
    if(_material == "tu" || { _material == "du" } ) then {
       _s2 = (_c0 + _c1 * _targetHardness) * _targetHardness / _projectileDensity;  
    } else {
        _s2 = (_c0 * (_projectileHardness^_k) * (_targetHardness^_n) ) / _projectileDensity;
    };
    
    _tanX = _b0 + _b1 * ( _workingLength / _projectileDiameter );
    _step_one = (1 / tanh(_tanX) );
    _step_two = ((cos _impactAngle) ^ _m);
    _step_three = sqrt ( _projectileDensity / _targetDensity);
    _step_four = __e ^ ( -(_s2) / ( _impactVelocity ^ 2) );
    _solve = _a * _step_one * _step_two * _step_three * _step_four;
    
    /* http://www.longrods.ch/bilder/perf_eq.jpg 
        
        D = _projectileDiameter
        L = _length, length of penetrator mm
        Lw = _workingLength, working length
        Vt = _impactVelocity, impact velocity km/s
        0/ = _impactAngle, angle of oblquity
        Pp = _projectileDensity, kg/m3
        Pt = _targetDensity, kg/m3
        d = _targetThickness, mm
        BHNP = _projectileHardness, hardness number penetration
        BHNT = _targetHardness, hardness number of targets
        P = _channelLength, perforation channel length in line of site mm
    
        // WOrking lengths:
        // http://www.longrods.ch/wlength.php
        // frustrum
        Lw = L - #L
        #L = Lf * (1-1/3(1+d/D+(d/D)^2))
        // cylindric penetration 
        _workingLength = Lw = L
    */
    
    
    
};