//
// Created by Peihong Yu on 3/2/21.
// Reference: https://blog.csdn.net/zhurui_idea/article/details/24782661
//

#ifndef RRT_SEARCH_VECTOR2D_H
#define RRT_SEARCH_VECTOR2D_H

#include <math.h>

class Vector2D {
public:
    float x,y;

    // construct functions
    Vector2D() {}

    Vector2D(const Vector2D &a) : x(a.x), y(a.y) {}

    Vector2D(float nx, float ny) : x(nx), y(ny) {}

    Vector2D &operator =(const Vector2D &a) {
        x = a.x; y = a.y;
        return *this;
    }

    bool operator ==(const Vector2D &a) const {
        return x==a.x && y==a.y;
    }

    bool operator !=(const Vector2D &a) const {
        return x!=a.x || y!=a.y;
    }

    void zero() { x = y = 0.0f; }

    Vector2D operator -() const {
        return Vector2D(-x, -y);
    }

    Vector2D operator +(const Vector2D &a) const {
        return Vector2D(x + a.x, y + a.y);
    }

    Vector2D operator -(const Vector2D &a) const {
        return Vector2D(x - a.x, y - a.y);
    }

    Vector2D operator *(float a) const {
        return Vector2D(x*a, y*a);
    }

    Vector2D operator /(float a) const {
        float oneOverA = 1.0f / a;
        return Vector2D(x*oneOverA, y*oneOverA);
    }

    Vector2D &operator +=(const Vector2D &a) {
        x += a.x; y += a.y;
        return *this;
    }
    Vector2D &operator -=(const Vector2D &a) {
        x -= a.x; y -= a.y;
        return *this;
    }
    Vector2D &operator *=(float a) {
        x *= a; y *= a;
        return *this;
    }
    Vector2D &operator /=(float a) {
        float oneOverA = 1.0f / a;
        x *= oneOverA; y *= oneOverA;
        return *this;
    }

    void normalize() {
        float magSq = x*x + y*y;
        if (magSq > 0.0f) {
            float oneOverMag = 1.0f / sqrt(magSq);
            x *= oneOverMag;
            y *= oneOverMag;
        }
    }

    float operator *(const Vector2D &a) const {
        return x*a.x + y*a.y;
    }
};

inline float vectorMag(const Vector2D &a) {
    return sqrt(a.x*a.x + a.y*a.y);
}

inline Vector2D operator *(float k, const Vector2D &v) {
    return Vector2D(k*v.x, k*v.y);
}

inline float distance(const Vector2D &a, const Vector2D &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

extern const Vector2D kZeroVector;

#endif //RRT_SEARCH_VECTOR2D_H
