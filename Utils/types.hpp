#include <type_traits>

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
        Vec3<T> operator*(const Vec3<T> &mult) {

        };
        ~Vec3() {

        };
        T _x, _y, _z;
};