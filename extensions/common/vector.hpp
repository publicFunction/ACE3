#pragma once

#include "shared.hpp"
namespace ace {
    template<typename T>
    class pair {
    public:
        pair() :
            _x(0),
            _y(0) {
        }
        pair(const T x_, const T y_, const T z_) :
            _x(x_),
            _y(y_) {
        }
        pair(const float *buffer) {
            _x = buffer[0];
            _y = buffer[1];
        }
        pair(std::istream & read_) {
            // Constructor to read from a stream
            read_.read((char *)&_x, sizeof(T));
            read_.read((char *)&_y, sizeof(T));
        }

        pair<T> & operator= (const pair<T>& other) { _x = other.x(); _y = other.y();  return *this; }

        const T & x() const { return _x; }
        const T & y() const { return _y; }

        void x(const T val) { _x = val; }
        void y(const T val) { _y = val; }
    protected:
        T _x;
        T _y;
    };

    template<typename T>
    class vector3 {
    public:
        vector3() :
            _x(0),
            _y(0),
            _z(0) {
        }
        vector3(const T x_, const T y_, const T z_) :
            _x(x_),
            _y(y_),
            _z(z_) {
        }
        vector3(std::istream & read_) {
            // Constructor to read from a stream
            read_.read((char *)&_x, sizeof(T));
            read_.read((char *)&_y, sizeof(T));
            read_.read((char *)&_z, sizeof(T));
        }
        vector3(const float *buffer) {
            _x = buffer[0];
            _y = buffer[1];
            _z = buffer[2];
        }

        vector3<T> & operator= (const vector3<T>& other) { _x = other.x(); _y = other.y(); _z = other.z(); return *this; }
/*#ifdef _WIN32 && _DIRECTX
        	vector3<T> & operator= (const XMFLOAT3& Float3) { _x = Float3.x; _y = Float3.y; _z = Float3.z; return *this; }
#endif
*/
        vector3 operator * (const T &val) const { return vector3(_x * val, _y * val, _z * val); }
        vector3 operator / (const T &val) const { T invVal = T(1) / val; return vector3(_x * invVal, _y * invVal, _z * invVal); }
        vector3 operator + (const vector3<T> &v) const { return vector3(_x + v.x(), _y + v.y(), _z + v.z()); }
        vector3 operator / (const vector3 &v) const { return vector3(_x / v.x(), _y / v.y(), _z / v.z()); }
        vector3 operator * (const vector3 &v) const { return vector3(_x * v.x(), _y * v.y(), _z * v.z()); }
        vector3 operator - (const vector3 &v) const { return vector3(_x - v.x(), _y - v.y(), _z - v.z()); }
        vector3 operator - () const { return vector3(-_x, -_y, -_z); }

        bool operator == (const vector3 &r) const { return (_x == r.x() && _y == r.y() && _z == r.z()); }
        bool operator >  (const vector3 &r) const { throw 1; }
        bool operator <  (const vector3 &r) const { throw 1; }
        bool operator <= (const vector3 &r) const { throw 1; }
        bool operator >= (const vector3 &r) const { throw 1; }

        T magnitude() const { return sqrt(_x * _x + _y * _y + _z * _z); }
        T dot(const vector3 &v) const { return (_x * v.x() + _y * v.y() + _z * v.z()); }
        T distance(const vector3 &v) const { return sqrt(dot(v)); }
        vector3 cross(const vector3 &v) const { return vector3(_y * v.z() - _z * v.y(), _z * v.x() - _x * v.z(), _x * v.y() - _y * v.x()); }

        const T & x() const { return _x; }
        const T & y() const { return _y; }
        const T & z() const { return _z; }

        void x(const T val) { _x = val; }
        void y(const T val) { _y = val; }
        void z(const T val) { _z = val; }
    protected:
        T _x;
        T _y;
        T _z;
    };

    template<typename T, unsigned int N = 3>
    class vector {
    public:
        vector() :
            _values(std::vector<T>(N)) {
        }
        std::vector<T> _values;
    };


    template<typename T>
    class spatial {
    public:
        spatial() :
            position(vector3<T>()),
            orientation(vector3<T>())
        {
        }
        explicit spatial(const vector3<T> & position_, const vector3<T> & orientation_) :
            position(position_),
            orientation(orientation_)
        {}
        spatial<T> & operator= (const spatial<T> & other) { position = other.position; orientation = other.orientation; return *this; }
        vector3<T> position;
        vector3<T> orientation;
    };
};