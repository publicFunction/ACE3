class CfgAmmo {
    class BulletCore;
    class ShellCore;
    class ShellBase;
    
    
    class Sh_120mm_APFSDS: ShellBase {
        ACE_projectileType = 2;
        
        ACE_bulletLength = 650;     // mm
        ACE_bulletDensity = 19100;  // This is lead, we should use tungsten/DU kg/m3
        ACE_caliber = 1.02362;      // caliber is diamter in inches
        ACE_bulletDiameter = 27;    // mm
        ACE_bulletMass = 4.6;       // kg
        ACE_frustumLength = 50;     // mm
        ACE_frustumDiameter =10;   // mm
    };
    
    class BulletBase: BulletCore {
        ACE_bulletDensity = 11300;  // 11.3g/cm3 or 11300kg/m3, this is the density of lead
    };
    
    // By default, lets assume uranium shells
    class ShellBase: ShellCore {
        ACE_bulletDensity = 7000;  // 11.3g/cm3 or 11300kg/m3, this is the density of lead, 7000 steel alloy
        ACE_bulletLength = 28.3465;
        ACE_caliber = 1.02362;
        ACE_bulletMass = 70989.1;
    };
};