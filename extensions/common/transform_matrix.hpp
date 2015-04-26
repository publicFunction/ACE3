#pragma once

#include "ace_common.h"
#include "vector.hpp"

namespace ace {
    template <typename T>
    class transform_matrix_base {
    public:
        transform_matrix_base<T> & operator= (const transform_matrix_base<T>& other) { _x = other.x(); _y = other.y(); _z = other.z(); _n = other.n();  return *this; }

        transform_matrix_base() {}
        transform_matrix_base(std::istream &stream_) : _x(stream_), _y(stream_), _z(stream_), _n(stream_) { }
        transform_matrix_base(ace::vector3<T> x_, ace::vector3<T> y_, ace::vector3<T> z_, ace::vector3<T> n_) : _x(x_), _y(y_), _z(z_), _n(n_) { }

        const T & x() const { return _x; }
        const T & y() const { return _y; }
        const T & z() const { return _z; }
        const T & n() const { return _n; }

        void x(const T val) { _x = val; }
        void y(const T val) { _y = val; }
        void z(const T val) { _z = val; }
        void n(const T val) { _n = val; }
    protected:
        ace::vector3<T> _x;
        ace::vector3<T> _y;
        ace::vector3<T> _z;
        ace::vector3<T> _n;
    };

    typedef transform_matrix_base<float> transform_matrix;
};