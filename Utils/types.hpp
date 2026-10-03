#ifndef TYPES_HPP
#define TYPES_HPP

#include <type_traits>
#include <iostream>
#include <cmath>
#include <concepts>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vec3 {
    public:
        Vec3() noexcept : _x(0), _y(0), _z(0) {};
        Vec3(T x, T y, T z) noexcept : _x(x), _y(y), _z(z) {};
        Vec3(T i) noexcept : _x(i), _y(i), _z(i) {};

        static constexpr T dotProduct(Vec3<T> v1, Vec3<T> v2) noexcept {
            return (v1._x * v2._x) + (v1._y * v2._y) + (v1._z * v2._z);
        };
        auto getMagnitude() const noexcept {
            return std::sqrt((this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z));
        };
        void normalize() noexcept requires std::floating_point<T> {
            T mag = this->getMagnitude();
            if (mag > 0) {
                T inverseMag = T(1) / mag; // Only 1 division, because division is slower than multiplication.
                this->_x *= inverseMag;
                this->_y *= inverseMag;
                this->_z *= inverseMag;
            }
        };
        Vec3<T> normalized() const noexcept requires std::floating_point<T> {
            Vec3<T> result(*this);
            result.normalize();
            return result;
        };
        Vec3<T> operator*(const Vec3<T> &mult) const noexcept {
            return Vec3<T>(this->_x * mult._x, this->_y * mult._y, this->_z * mult._z);
        };
        Vec3<T> operator*(const T &mult) const noexcept {
            return Vec3<T>(this->_x * mult, this->_y * mult, this->_z * mult);
        };
        Vec3<T> operator+(const Vec3<T> &add) const noexcept {
            return Vec3<T>(this->_x + add._x, this->_y + add._y, this->_z + add._z);
        };
        Vec3<T> &operator+=(const Vec3<T> &add) noexcept {
            this->_x += add._x;
            this->_y += add._y;
            this->_z += add._z;
            return *this;
        };
        Vec3<T> operator-(const Vec3<T> &sub) const noexcept {
            return Vec3<T>(this->_x - sub._x, this->_y - sub._y, this->_z - sub._z);
        };
        Vec3<T> &operator-=(const Vec3<T> &sub) noexcept {
            this->_x -= sub._x;
            this->_y -= sub._y;
            this->_z -= sub._z;
            return *this;
        };
        ~Vec3() = default;
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
        Vec2() noexcept : _x(0), _y(0) {};
        Vec2(T x, T y) noexcept : _x(x), _y(y) {};
        Vec2(T i) noexcept : _x(i), _y(i) {};

        static constexpr T dotProduct(Vec2<T> v1, Vec2<T> v2) noexcept {
            return (v1._x * v2._x) + (v1._y * v2._y);
        };
        auto getMagnitude() const noexcept {
            return std::sqrt((this->_x * this->_x) + (this->_y * this->_y));
        };
        void normalize() noexcept requires std::floating_point<T> {
            T mag = this->getMagnitude();
            if (mag > 0) {
                T inverseMag = T(1) / mag; // Only 1 division, because division is slower than multiplication.
                this->_x *= inverseMag;
                this->_y *= inverseMag;
            }
        };
        Vec2<T> normalized() noexcept requires std::floating_point<T> {
            Vec2<T> result(*this);
            result.normalize();
            return result;
        };
        Vec2<T> operator*(const Vec2<T> &mult) const noexcept {
            return Vec2<T>(this->_x * mult._x, this->_y * mult._y);
        };
        Vec2<T> operator*(const T &mult) const noexcept{
            return Vec2<T>(this->_x * mult, this->_y * mult);
        };
        Vec2<T> &operator*=(const Vec2<T> &mult) noexcept {
            this->_x *= mult._x;
            this->_y *= mult._y;
            return *this;
        };
        Vec2<T> operator+(const Vec2<T> &add) const noexcept {
            return Vec2<T>(this->_x + add._x, this->_y + add._y);
        };
        Vec2<T> &operator+=(const Vec2<T> &add) noexcept {
            this->_x += add._x;
            this->_y += add._y;
            return *this;
        };
        Vec2<T> operator-(const Vec2<T> &sub) const noexcept {
            return Vec2<T>(this->_x - sub._x, this->_y - sub._y);
        };
        Vec2<T> &operator-=(const Vec2<T> &sub) noexcept {
            this->_x -= sub._x;
            this->_y -= sub._y;
            return *this;
        };
        ~Vec2() = default;
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
        Matrix2x2() noexcept : _x1(0), _x2(0), _y1(0), _y2(0) {
        };
        Matrix2x2(T x1, T x2, T y1, T y2) noexcept : _x1(x1), _x2(x2), _y1(y1), _y2(y2) {
        };
        Matrix2x2(T i) noexcept : _x1(i), _x2(i), _y1(i), _y2(i) {
        };
        Matrix2x2<T> operator*(T mult) const noexcept {
            return Matrix2x2<T>(this->_x1 * mult, this->_x2 * mult, this->_y1 * mult, this->_y2 * mult);
        };
        Matrix2x2<T> &operator*=(T mult) noexcept {
            this->_x1 *= mult;
            this->_x2 *= mult;
            this->_y1 *= mult;
            this->_y2 *= mult;
            return *this;
        };
        Matrix2x2<T> operator+(const Matrix2x2<T> &add) const noexcept {
            return Matrix2x2(this->_x1 + add._x1, this->_x2 + add._x2, this->_y1 + add._y1, this->_y2 + add._y2);
        };
        Matrix2x2<T> &operator+=(const Matrix2x2<T> &add) noexcept {
            this->_x1 += add._x1;
            this->_x2 += add._x2;
            this->_y1 += add._y1;
            this->_y2 += add._y2;
            return *this;
        };
        Matrix2x2<T> operator-(const Matrix2x2<T> &sub) const noexcept {
            return Matrix2x2(this->_x1 - sub._x1, this->_x2 - sub._x2, this->_y1 - sub._y1, this->_y2 - sub._y2);
        };
        Matrix2x2<T> &operator-=(const Matrix2x2<T> &sub) noexcept {
            this->_x1 -= sub._x1;
            this->_x2 -= sub._x2;
            this->_y1 -= sub._y1;
            this->_y2 -= sub._y2;
            return *this;
        };
        T _x1, _x2, _y1, _y2;
    private:
        friend std::ostream& operator<<(std::ostream &os, const Matrix2x2<T> m) {
            os << "[" << m._x1 << ", " << m._x2 << "]" << std::endl << "[" << m._y1 << ", " << m._y2 << "]";
            return os;
        }
};

#endif  // TYPES_HPP
