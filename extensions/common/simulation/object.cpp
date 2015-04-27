#include "object.hpp"
#include "p3d\parser.hpp"

ace::simulation::object::object()
{
}

ace::simulation::object::object(std::string &filepath) : _p3d_path(filepath)
{
	ace::p3d::parser parser;
	_p3d = parser.load(_p3d_path);
}

ace::simulation::object::~object()
{
}
