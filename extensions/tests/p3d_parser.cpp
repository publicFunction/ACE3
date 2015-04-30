#include "shared.hpp"
#include "p3d\parser.hpp"
#include "simulation\object.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
    ace::p3d::parser _parser;
	
    el::Configurations log_conf;
    log_conf.setGlobally(el::ConfigurationType::Filename, "logs/server.log");

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
    ace::p3d::model_p model = _parser.load(argv[1]);

	ace::simulation::object _object(model);

    getchar();

    return 0;
} 