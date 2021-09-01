#include <type_traits>
#include <iostream>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vec3 {
    public:
        explicit Vec3() {
            this->_x = 0;
            this->_y = 0;
            this->_z = 0;
        };
        Vec3(T x, T y, T z) {
            this->_x = x;
            this->_y = y;
            this->_z = z;
        };
        Vec3(T i) {
            this->_x = i;
            this->_y = i;
            this->_z = i;
        };
        Vec3<T> operator*(const Vec3<T> &mult) {
            T x = (this->_y * mult._z) - (this->_z * mult._y);
            T y = (this->_x * mult._z) - (this->_z * mult._x);
            T z = (this->_x * mult._y) - (this->_y * mult._x);
            return Vec3<T>(x, y, z);
        };
        Vec3<T> operator*(const T &mult) {
            this->_x *= mult;
            this->_y *= mult;
            this->_z *= mult;
        }
        friend std::ostream& operator<<(std::ostream &os, const Vec3<T> v) {
            os << v._x << ", " << v._y << ", " << v._z;
            return os;
        }
        ~Vec3() {

        };
        T _x, _y, _z;
};