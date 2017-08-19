
#pragma once

#include "../deps.h"

class Mat33 {
  public:
    float _00, _10, _20, _01, _11, _21, _02, _12, _22;

    Mat33(float _00, float _10, float _20, float _01, float _11, float _21,
          float _02, float _12, float _22)
        : _00(_00), _10(_10), _20(_20), _01(_01), _11(_11), _21(_21), _02(_02),
          _12(_12), _22(_22) {}

    void setFrom(const Mat33 &m) {
        this->_00 = m._00;
        this->_10 = m._10;
        this->_20 = m._20;

        this->_01 = m._01;
        this->_11 = m._11;
        this->_21 = m._21;

        this->_02 = m._02;
        this->_12 = m._12;
        this->_22 = m._22;
    }

    static Mat33 translation(float x, float y) {
        return Mat33(1, 0, x, 0, 1, y, 0, 0, 1);
    }

    static Mat33 empty() { return Mat33(0, 0, 0, 0, 0, 0, 0, 0, 0); }

    static Mat33 identity() { return Mat33(1, 0, 0, 0, 1, 0, 0, 0, 1); }

    static Mat33 scale(float x, float y) {
        return Mat33(x, 0, 0, 0, y, 0, 0, 0, 1);
    }

    static Mat33 rotation(float alpha) {
        return Mat33(std::cos(alpha), -std::sin(alpha), 0, std::sin(alpha),
                     std::cos(alpha), 0, 0, 0, 1);
    }

    Mat33 add(const Mat33 &m) const {
        return Mat33(_00 + m._00, _10 + m._10, _20 + m._20, _01 + m._01,
                     _11 + m._11, _21 + m._21, _02 + m._02, _12 + m._12,
                     _22 + m._22);
    }

    Mat33 sub(const Mat33 &m) const {
        return Mat33(00 - m._00, _10 - m._10, _20 - m._20, _01 - m._01,
                     _11 - m._11, _21 - m._21, _02 - m._02, _12 - m._12,
                     _22 - m._22);
    }

    Mat33 mult(float value) const {
        return Mat33(_00 * value, _10 * value, _20 * value, _01 * value,
                     _11 * value, _21 * value, _02 * value, _12 * value,
                     _22 * value);
    }

    Mat33 transpose() const {
        return Mat33(_00, _01, _02, _10, _11, _12, _20, _21, _22);
    }

    float trace() const { return _00 + _11 + _22; }

    Mat33 multmat(const Mat33 &m) const {
        return Mat33(00 * m._00 + _10 * m._01 + _20 * m._02,
                     _00 * m._10 + _10 * m._11 + _20 * m._12,
                     _00 * m._20 + _10 * m._21 + _20 * m._22,
                     _01 * m._00 + _11 * m._01 + _21 * m._02,
                     _01 * m._10 + _11 * m._11 + _21 * m._12,
                     _01 * m._20 + _11 * m._21 + _21 * m._22,
                     _02 * m._00 + _12 * m._01 + _22 * m._02,
                     _02 * m._10 + _12 * m._11 + _22 * m._12,
                     _02 * m._20 + _12 * m._21 + _22 * m._22);
    }

    inline float cofactor(float m0, float m1, float m2, float m3) const {
        return m0 * m3 - m1 * m2;
    }

    float determinant() const {
        float c00 = cofactor(_11, _21, _12, _22);
        float c01 = cofactor(_10, _20, _12, _22);
        float c02 = cofactor(_10, _20, _11, _21);
        return _00 * c00 - _01 * c01 + _02 * c02;
    }

    Mat33 inverse() const {
		float c00 = cofactor(_11, _21, _12, _22);
        float c01 = cofactor(_10, _20, _12, _22);
        float c02 = cofactor(_10, _20, _11, _21);

        float det = _00 * c00 - _01 * c01 + _02 * c02;
        if (std::abs(det) < 0.000001) {
            throw "determinant is too small";
        }

        float c10 = cofactor(_01, _21, _02, _22);
        float c11 = cofactor(_00, _20, _02, _22);
        float c12 = cofactor(_00, _20, _01, _21);

        float c20 = cofactor(_01, _11, _02, _12);
        float c21 = cofactor(_00, _10, _02, _12);
        float c22 = cofactor(_00, _10, _01, _11);

        float invdet = 1.0f / det;
        return Mat33(
            c00 * invdet,  -c01 * invdet,  c02 * invdet,
            -c10 * invdet,  c11 * invdet, -c12 * invdet,
            c20 * invdet,  -c21 * invdet,  c22 * invdet
        );
    }
};
