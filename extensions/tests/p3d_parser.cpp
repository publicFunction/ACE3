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
    ace::p3d::model_p _model = _parser.load(argv[1]);

	ace::simulation::object _object(_model);
	printf("lod 0 face 0: %d %d %d", _object.lods[0]->faces[0]->vertex_table[0],
		_object.lods[0]->faces[0]->vertex_table[1],
		_object.lods[0]->faces[0]->vertex_table[2]);
	uint16_t vertId = _object.lods[0]->faces[0]->vertex_table[0];
	printf("lod 0 face 0 vertex 0: %f %f %f", _object.lods[0]->vertices[vertId].x(),
		_object.lods[0]->vertices[vertId].y(),
		_object.lods[0]->vertices[vertId].z());

    getchar();

    return 0;
} 