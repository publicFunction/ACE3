#include "ace_common.h"
#include "p3d\parser.hpp"
#include "simulation\object.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
    //ace::p3d::parser _parser;
	

#ifdef _DEBUG
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "[%datetime] - %level - {%loc}t:%thread- %msg");
    //%d%M%Y-%H:%m:%s.%g			
#else
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-{%level}- %msg");
#endif

    if (argc < 2) {
        printf("Usage: %s [file.p3d]", argv[0]);
        return -1;
    }
    //_parser.load(argv[1]);

	ace::simulation::object _object(std::string(argv[1]));

    getchar();

    return 0;
} 