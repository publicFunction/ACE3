#include "shared.hpp"

#include "logging.hpp"
INITIALIZE_EASYLOGGINGPP
#include "pbo/search.hpp"
#include "vector.hpp"

#ifdef _DEBUG
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Dynamics_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Collision_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Common_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/LinearMath_vs2010_debug.lib")
#else
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Dynamics_vs2010_debug.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Collision_vs2010.lib")
#pragma comment(lib, "../../lib/bullet3/lib/Bullet3Common_vs2010.lib")
#pragma comment(lib, "../../lib/bullet3/lib/LinearMath_vs2010.lib")
#endif

/*
extern "C" {
    __declspec (dllimport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};*/
void __stdcall RVExtension(char *output, int outputSize, const char *function);

int main(int argc, char **argv) {
    char buffer[4096], output[4096];
    std::ifstream filestream;

#ifdef _DEBUG
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "[%datetime] - %level - {%loc}t:%thread- %msg");
    //%d%M%Y-%H:%m:%s.%g			
#else
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-{%level}- %msg");
#endif

    filestream.open(argv[1], std::ios::binary | std::ios::in);
    if (!filestream.good()) {
        LOG(ERROR) << "Cannot open file";
        return -1;
    }


    while (true) {
        scanf_s("%s", buffer, sizeof(buffer)-1);
        memset(output, 0x00, sizeof(output));
        LOG(INFO) << "Executing: '" << buffer << "'";
        RVExtension(output, sizeof(output), buffer);
        LOG(INFO) << "Result: '" << output << "'";
    }

}