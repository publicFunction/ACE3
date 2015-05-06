#include "shared.hpp"
#include "logging.hpp"

INITIALIZE_EASYLOGGINGPP

#define BT_NO_SIMD_OPERATOR_OVERLOADS
#include "btBulletCollisionCommon.h"

#ifndef _STATIC
#ifdef _DEBUG
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Dynamics_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Collision_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Common_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/LinearMath_vs2010_debug.lib")
#else
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Dynamics_vs2010.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Collision_vs2010.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Common_vs2010.lib")
#pragma comment(lib, "../../lib/bullet3/lib/LinearMath_vs2010.lib")
#endif
#endif

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
    IN DWORD     nReason,
    IN LPVOID    Reserved) {
    BOOLEAN bSuccess = TRUE;
    el::Configurations conf;

    switch (nReason) {
    case DLL_PROCESS_ATTACH:
        conf.setGlobally(el::ConfigurationType::Filename, "logs/ace_vd.log");
        el::Loggers::setDefaultConfigurations(conf, true);

        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return bSuccess;

}