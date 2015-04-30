#include "object.hpp"
#include "p3d\parser.hpp"

ace::simulation::named_selection::named_selection(
	const ace::p3d::named_selection_p p3d_selection,
	const ace::p3d::lod_p p3d_lod,
	const ace::p3d::model_p p3d)
{

}

ace::simulation::named_selection::~named_selection()
{
}

ace::simulation::face::face(
	const ace::p3d::face_p p3d_face,
	const ace::p3d::lod_p p3d_lod,
	const ace::p3d::model_p p3d)
{

}

ace::simulation::face::~face()
{
}

ace::simulation::lod::lod(const ace::p3d::lod_p p3d_lod, const ace::p3d::model_p p3d)
{
	this->id = p3d_lod->id;
	this->vertices.resize(p3d_lod->vertices->points.size);
	for (uint32_t i = 0; i <= p3d_lod->vertices->points.size-1; ++i) {
		this->vertices[i] = p3d_lod->vertices->points[i];
	}
	this->animated_vertices.resize(p3d_lod->vertices->points.size);

	for (ace::p3d::named_selection_p p3d_selection : p3d_lod->selections) {
		this->selections[p3d_selection->name] = std::make_shared<named_selection>(p3d_selection, p3d_lod, p3d);
	}

	for (ace::p3d::face_p p3d_face : p3d_lod->faces) {
		this->faces.push_back(std::make_shared<face>(p3d_face, p3d_lod, p3d));
	}
}


ace::simulation::lod::~lod()
{
}

ace::simulation::lod_animation_bone::lod_animation_bone(
	const ace::p3d::animate_bone_p p3d_animate_bone,
	const ace::p3d::animation_p p3d_animation,
	const ace::p3d::model_p p3d)
{
	this->index = p3d_animate_bone->index;
	this->lod = p3d_animate_bone->lod;
	this->axis_position = p3d_animate_bone->axis_position;
	this->axis_direction = p3d_animate_bone->axis_direction;
}

ace::simulation::lod_animation_bone::~lod_animation_bone()
{
}

ace::simulation::animation::animation(const ace::p3d::animation_p p3d_animation, const ace::p3d::model_p p3d)
{
	this->type = p3d_animation->type;
	this->name = p3d_animation->name;
	this->source = p3d_animation->source;

	this->minmax_value[0] = p3d_animation->minmax_value[0];
	this->minmax_value[1] = p3d_animation->minmax_value[1];

	this->minmax_phase[0] = p3d_animation->minmax_phase[0];
	this->minmax_phase[1] = p3d_animation->minmax_phase[1];

	this->source_address = p3d_animation->source_address;

	this->transforms = p3d_animation->transforms;

	for (ace::p3d::animate_bone_p animation_bone : p3d_animation->bones) {
		this->lod_animations[animation_bone->lod] = std::make_shared<lod_animation_bone>(animation_bone, p3d_animation, p3d);
	}

}

ace::simulation::animation::~animation()
{
}

ace::simulation::object::object()
{
}

ace::simulation::object::object(const ace::p3d::model_p model)
{
	for (ace::p3d::lod_p p3d_lod : model->lods) {
		lod_p new_lod = std::make_shared<lod>(p3d_lod, model);
		this->lods[p3d_lod->id] = new_lod;
		this->available_lods.push_back(p3d_lod->id);
	}

	for (ace::p3d::animation_p p3d_animation : model->animations) {
		this->animations.push_back(std::make_shared<animation>(p3d_animation, model));
	}
}



ace::simulation::object::~object()
{
}

