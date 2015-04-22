class CfgAmmo {
    class BulletCore;
    class ShellCore;
    
    class BulletBase: BulletCore {
        ACE_bulletDensity = 11300;  // 11.3g/cm3 or 11300kg/m3, this is the density of lead
    };
    
    // By default, lets assume uranium shells
    class ShellBase: ShellCore {
        ACE_bulletDensity = 7000;  // 11.3g/cm3 or 11300kg/m3, this is the density of lead, 7000 steel alloy
        ACE_bulletLength = 720.3465;
        ACE_caliber = 0.944882;
    };
};