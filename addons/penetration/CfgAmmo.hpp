class CfgAmmo {
    class BulletCore;
    class ShellCore;
    
    class BulletBase: BulletCore {
        GVAR(density) = 11300;  // 11.3g/cm3 or 11300kg/m3, this is the density of lead
    };
    
    // By default, lets assume uranium shells
    class ShellBase: ShellCore {
        GVAR(density) = 19100;  // 11.3g/cm3 or 11300kg/m3, this is the density of lead
    };
};