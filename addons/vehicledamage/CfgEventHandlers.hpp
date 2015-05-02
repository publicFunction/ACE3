
class Extended_PreInit_EventHandlers {
    class ADDON {
        init = QUOTE(call COMPILE_FILE(XEH_preInit));
    };
};

class Extended_PostInit_EventHandlers {
    class ADDON {
        init = QUOTE(call COMPILE_FILE(XEH_postInit));
    };
};

class Extended_Init_EventHandlers {
	class Tank {
		GVAR(registerWithExtension) = QUOTE(_this call FUNC(registerVehicleWithExtension));
		GVAR(registerDamageHandler) = QUOTE(_this call FUNC(registerVehicleDamageHandler));
	};
	class Wheeled_APC {
        GVAR(registerWithExtension) = QUOTE(_this call FUNC(registerVehicleWithExtension));
		GVAR(registerDamageHandler) = QUOTE(_this call FUNC(registerVehicleDamageHandler));
	};
};