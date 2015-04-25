#pragma once

#include "ace_common.h"
#include "vector.hpp"

namespace ace {
    template <typename T>
    class transform_matrix_base {
    public:

        ace::vector3<T> x;
        ace::vector3<T> y;
        ace::vector3<T> z;
        ace::vector3<T> n;

        transform_matrix_base() {}
        transform_matrix_base(std::fstream &stream_) : x(stream_), y(stream_), z(stream_), n(stream_) { }
        transform_matrix_base(ace::vector3<T> x_, ace::vector3<T> y_, ace::vector3<T> z_, ace::vector3<T> n_) : x(x_), y(y_), z(z_), n(n_) { }
    };

    typedef transform_matrix_base<float> transform_matrix;
};