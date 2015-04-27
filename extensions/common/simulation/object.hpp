#pragma once

#include "ace_common.h"

#include <string>

#include "p3d\model.hpp"

namespace ace {
	namespace simulation {
		class object {
		public:
			object();
			object(std::string &);
			~object();

		protected:
			ace::p3d::model_p _p3d;
			std::string _p3d_path;
		};
	}
}