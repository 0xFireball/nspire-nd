
#pragma once

#include <cmath>

#include "Mat33.h"

class Vec2 {
  private:
    float _x, _y;

  public:
    Vec2(float x, float y) : _x(x), _y(y) {}
    Vec2(float v) : Vec2(v, v) {}
    Vec2() : Vec2(0) {}

    float getX() const { return _x; }
    float getY() const { return _y; }

    void setX(float x) { _x = x; }
    void setY(float y) { _y = y; }

    void copyFrom(const Vec2 &other) {
        _x = other.getX();
        _y = other.getY();
    }

    void set(float x, float y) {
        _x = x;
        _y = y;
    }

    float length() { return std::sqrt(_x * _x + _y * _y); }

    Vec2 operator+(const Vec2 &v2) const {
        return Vec2(_x + v2._x, _y + v2._y);
    }

    friend Vec2 &operator+=(Vec2 &v1, const Vec2 &v2) {
        v1._x += v2._x;
        v1._y += v2._y;
        return v1;
    }

    Vec2 operator*(float scalar) { return Vec2(_x * scalar, _y * scalar); }

    Vec2 &operator*=(float scalar) {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }

    Vec2 operator-(const Vec2 &v2) const {
        return Vec2(_x - v2._x, _y - v2._y);
    }
    friend Vec2 &operator-=(Vec2 &v1, const Vec2 &v2) {
        v1._x -= v2._x;
        v1._y -= v2._y;
        return v1;
    }

    Vec2 operator/(float scalar) { return Vec2(_x / scalar, _y / scalar); }
    Vec2 &operator/=(float scalar) {
        _x /= scalar;
        _y /= scalar;
        return *this;
    }

    Vec2 &normalize() {
        float l = length();
        if (l > 0) {
            (*this) *= 1 / l;
        }
        return *this;
    }

    float dot(const Vec2 &v) { return _x * v.getX() + _y * v.getY(); }

    void transform(const Mat33 &mat) {
        float w = mat._02 * _x + mat._12 * _y + mat._22 * 1;
        float x = (mat._00 * _x + mat._10 * _y + mat._20 * 1) / w;
        float y = (mat._01 * _x + mat._11 * _y + mat._21 * 1) / w;
        set(x, y);
    }
};
