
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
		GVAR(registerDamageHandler) = QUOTE(_this call FUNC(registerDamageHandler));
	};
	/*class Wheeled_APC {
		GVAR(add_hd_wapc) = QUOTE(_this call FUNC(wapc_add_hdeh));
	};*/
};