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
        static T dotProduct(Vec3<T> v1, Vec3<T> v2) {
            return (v1._x * v2._x) + (v1._y * v2._y) + (v1._z * v2._z);
        }
        // ! operator* overloads may need some refactor, I don't really like how they are implemented atm.
        Vec3<T> operator*(const Vec3<T> &mult) {
            T x = (this->_y * mult._z) - (this->_z * mult._y);
            T y = (this->_x * mult._z) - (this->_z * mult._x);
            T z = (this->_x * mult._y) - (this->_y * mult._x);
            return Vec3<T>(x, y, z);
        };
        Vec3<T> operator*(const T &mult) {
            T x = this->_x * mult;
            T y = this->_y * mult;
            T z = this->_z * mult;
            return Vec3<T>(x, y, z);
        }
        ~Vec3() {

        };
        T _x, _y, _z;
    private:
        friend std::ostream& operator<<(std::ostream &os, const Vec3<T> v) {
            os << v._x << ", " << v._y << ", " << v._z;
            return os;
        }
};