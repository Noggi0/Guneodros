#include <type_traits>
#include <iostream>
#include <math.h>

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
        };
        const T getMagnitude() const {
            return sqrt((this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z));
        };
        void normalize() {
            T mag = this->getMagnitude();
            if (mag > 0) {
                this->_x /= mag;
                this->_y /= mag;
                this->_z /= mag;
            }
        };
        // ! operator* overloads may need some refactor, I don't really like how they are implemented atm.
        Vec3<T> operator*(const Vec3<T> &mult) {
            T x = (this->_y * mult._z) - (this->_z * mult._y);
            T y = (this->_x * mult._z) - (this->_z * mult._x);
            T z = (this->_x * mult._y) - (this->_y * mult._x);
            return Vec3<T>(x, y, z);
        };
        Vec3<T> &operator*(const T &mult) {
            T x = this->_x * mult._x;
            T y = this->_y * mult._y;
            T z = this->_z * mult._z;
            return Vec3<T>(x, y, z);
        };
        Vec3<T> &operator*=(const Vec3<T> &mult) {
            this->_x *= mult._x;
            this->_y *= mult._y;
            this->_z *= mult._z;
            return *this;
        };
        Vec3<T> &operator+(const Vec3<T> &add) {
            T x = this->_x + add._x;
            T y = this->_y + add._y;
            T z = this->_z + add._z;
            return Vec3<T>(x, y, z);
        };
        Vec3<T> &operator+=(const Vec3<T> &add) {
            this->_x += add._x;
            this->_y += add._y;
            this->_z += add._z;
            return *this;
        };
        Vec3<T> &operator-(const Vec3<T> &sub) {
            T x = this->_x - sub._x;
            T y = this->_y - sub._y;
            T z = this->_z - sub._z;
            return Vec3<T>(x, y, z);
        };
        Vec3<T> &operator-=(const Vec3<T> &sub) {
            this->_x -= sub._x;
            this->_y -= sub._y;
            this->_z -= sub._z;
            return *this;
        };
        ~Vec3() {

        };
        T _x, _y, _z;
    private:
        friend std::ostream& operator<<(std::ostream &os, const Vec3<T> v) {
            os << "x:" <<v._x << ", y:" << v._y << ", z:" << v._z;
            return os;
        }
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vec2 {
    public:
        explicit Vec2() {
            this->_x = 0;
            this->_y = 0;
        };
        Vec2(T x, T y) {
            this->_x = x;
            this->_y = y;
        };
        Vec2(T i) {
            this->_x = i;
            this->_y = i;
        };
        static T dotProduct(Vec2<T> v1, Vec2<T> v2) {
            return (v1._x * v2._x) + (v1._y * v2._y);
        };
        const T getMagnitude() const {
            return sqrt((this->_x * this->_x) + (this->_y * this->_y));
        };
        void normalize() {
            T mag = this->getMagnitude();
            if (mag > 0) {
                this->_x /= mag;
                this->_y /= mag;
            }
        };
        // ! operator* overloads may need some refactor, I don't really like how they are implemented atm.
        Vec2<T> operator*(const Vec2<T> &mult) {
            T x = (this->_y * mult._z) - (this->_z * mult._y);
            T y = (this->_x * mult._z) - (this->_z * mult._x);
            return Vec2<T>(x, y);
        };
        Vec2<T> &operator*(const T &mult) {
            T x = this->_x * mult;
            T y = this->_y * mult;
            return Vec2<T>(x, y);
        };
        Vec2<T> &operator*=(const Vec2<T> &mult) {
            this->_x *= mult._x;
            this->_y *= mult._y;
            return *this;
        };
        Vec2<T> &operator+(const Vec2<T> &add) {
            T x = this->_x + add._x;
            T y = this->_y + add._y;
            T z = this->_z + add._z;
            return Vec2<T>(x, y, z);
        };
        Vec2<T> &operator+=(const Vec2<T> &add) {
            this->_x += add._x;
            this->_y += add._y;
            return *this;
        };
        Vec2<T> &operator-(const Vec2<T> &sub) {
            T x = this->_x - sub._x;
            T y = this->_y - sub._y;
            return Vec3<T>(x, y);
        };
        Vec2<T> &operator-=(const Vec2<T> &sub) {
            this->_x -= sub._x;
            this->_y -= sub._y;
            return *this;
        };
        ~Vec2() {

        };
        T _x, _y;
    private:
        friend std::ostream& operator<<(std::ostream &os, const Vec2<T> v) {
            os << "x:" << v._x << ", y:" << v._y;
            return os;
        }
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Matrix2x2 {
    public:
        explicit Matrix2x2() {
            this->_x1 = 0;
            this->_x2 = 0;
            this->_y1 = 0;
            this->_y2 = 0;
        };
        Matrix2x2(T x1, T x2, T y1, T y2) {
            this->_x1 = x1;
            this->_x2 = x2;
            this->_y1 = y1;
            this->_y2 = y2;
        };
        Matrix2x2(T i) {
            this->_x1 = i;
            this->_x2 = i;
            this->_y1 = i;
            this->_y2 = i;
        }
        Matrix2x2<T> &operator*(T mult) {
            T x1 = this->_x1 * mult;
            T x2 = this->_x2 * mult;
            T y1 = this->_y1 * mult;
            T y2 = this->_y2 * mult;
            return Matrix2x2<T>(x1, x2, y1, y2);
        };
        Matrix2x2<T> &operator*=(T mult) {
            this->_x1 *= mult._x1;
            this->_x2 *= mult._x2;
            this->_y1 *= mult._y1;
            this->_y2 *= mult._y2;
            return *this;
        }
        Matrix2x2<T> &operator+(Matrix2x2<T> add) {
            T x1 = this->_x1 + add._x1;
            T x2 = this->_x2 + add._x2;
            T y1 = this->_y1 + add._y1;
            T y2 = this->_y2 + add._y2;
            return Matrix2x2(x1, x2, y1, y2);
        };
        Matrix2x2<T> &operator+=(Matrix2x2<T> add) {
            this->_x1 += add._x1;
            this->_x2 += add._x2;
            this->_y1 += add._y1;
            this->_y2 += add._y2;
            return *this;
        };
        Matrix2x2<T> &operator-(Matrix2x2<T> sub) {
            T x1 = this->_x1 - add._x1;
            T x2 = this->_x2 - add._x2;
            T y1 = this->_y1 - add._y1;
            T y2 = this->_y2 - add._y2;
            return Matrix2x2(x1, x2, y1, y2);
        };
        Matrix2x2<T> &operator-=(Matrix2x2<T> sub) {
            this->_x1 -= add._x1;
            this->_x2 -= add._x2;
            this->_y1 -= add._y1;
            this->_y2 -= add._y2;
            return *this;
        };
        T _x1, _x2, _y1, _y2;
    private:
        friend std::ostream& operator<<(std::ostream &os, const Matrix2x2<T> m) {
            os << "[" << m._x1 << ", " << m._x2 << "]" << std::endl << "[" << m._y1 << ", " << m._y2 << "]";
            return os;
        }
};