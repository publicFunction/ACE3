#pragma once

#include "ace_common.h"
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

        vector3<T> & operator= (const vector3<T>& other) { _x = other.x(); _y = other.y(); _z = other.z(); return *this; }
/*#ifdef _WIN32 && _DIRECTX
        	vector3<T> & operator= (const XMFLOAT3& Float3) { _x = Float3.x; _y = Float3.y; _z = Float3.z; return *this; }
#endif
*/
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