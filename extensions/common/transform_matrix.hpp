#pragma once

#include "ace_common.h"
#include "vector.hpp"

namespace ace {
    class transform_matrix {
    public:

        ace::vector3<float> x;
        ace::vector3<float> y;
        ace::vector3<float> z;
        ace::vector3<float> n;

        transform_matrix() {}
        transform_matrix(std::fstream &stream_) : x(stream_), y(stream_), z(stream_), n(stream_) { }
        transform_matrix(ace::vector3<float> x_, ace::vector3<float> y_, ace::vector3<float> z_, ace::vector3<float> n_) : x(x_), y(y_), z(z_), n(n_) { }
    };
};