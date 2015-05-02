#pragma once

#include "shared.hpp"

#include <string>
#include <vector>
#include <map>

#include "p3d\model.hpp"

namespace ace {
	namespace simulation {


		class face {
		public:
			face() {};
			face(const ace::p3d::face_p, const ace::p3d::lod_p, const ace::p3d::model_p);
			~face();
			uint8_t type;
			std::vector<uint16_t> vertex_table;
		};
		typedef std::shared_ptr<face> face_p;

		class named_selection {
		public:
			named_selection() {};
			named_selection(const ace::p3d::named_selection_p, const ace::p3d::lod_p, const ace::p3d::model_p);
			~named_selection();

			std::string name;
			std::vector<uint16_t> faces;
			std::vector<uint16_t> vertex_table;
		};
		typedef std::shared_ptr<named_selection> named_selection_p;

		class vertex_table {
		public:
			vertex_table() {};
			vertex_table(const ace::p3d::vertex_table_p, const ace::p3d::lod_p, const ace::p3d::model_p);
			~vertex_table();
			void animate(ace::transform_matrix m);
			size_t size() { return vertices_animated.size(); }
			void reset() { this->vertices_animated = this->vertices; }
			ace::vector3<float> & operator[] (uint16_t index) { return vertices_animated[index]; }

		protected:
			std::vector<ace::vector3<float>> vertices;
			std::vector<ace::vector3<float>> vertices_animated;
		};

		class lod {
		public:
			lod() {};
			lod(const ace::p3d::lod_p, const ace::p3d::model_p);
			~lod();
			uint32_t id;
			vertex_table vertices;
			std::map<std::string, named_selection_p> selections;
			std::vector<face_p> faces;
		};
		typedef std::shared_ptr<lod> lod_p;

		class lod_animation_bone {
		public:
			lod_animation_bone() {};
			lod_animation_bone(const ace::p3d::animate_bone_p, const ace::p3d::animation_p, const ace::p3d::model_p);
			~lod_animation_bone();
			int32_t index;
			uint32_t lod;
			ace::vector3<float> axis_direction;
			ace::vector3<float> axis_position;
		};
		typedef std::shared_ptr<lod_animation_bone> lod_animation_bone_p;

		class animation {
		public:
			animation() {};
			animation(const ace::p3d::animation_p, const ace::p3d::model_p);
			~animation();

			uint32_t        type;
			std::string     name;  // "RightDoor"
			std::string     source;     // "rotor"
			float           minmax_value[2];
			float           minmax_phase[2];
			uint32_t        source_address;

			std::vector<float> transforms;
			std::map<uint32_t, lod_animation_bone_p> lod_animations;
		};
		typedef std::shared_ptr<animation> animation_p;

		class object {
		public:
			object();
			object(const ace::p3d::model_p);
			~object();

			std::map<uint32_t, lod_p> lods;
			std::vector<uint32_t> available_lods;

			std::vector<animation_p> animations;


		};
		typedef std::shared_ptr<object> object_p;
	}
}