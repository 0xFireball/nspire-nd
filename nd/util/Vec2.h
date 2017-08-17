
#pragma once

#include <cmath>

class Vec2 {
  private:
    float _x, _y;

  public:
    Vec2(float x, float y) : _x(x), _y(y) {}
    Vec2(float v) : Vec2(v, v) {}

    float getX() { return _x; }
    float getY() { return _y; }

    void setX(float x) { _x = x; }
    void setY(float y) { _y = y; }

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
};
