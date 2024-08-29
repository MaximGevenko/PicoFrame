#ifndef _VECTOR2D_H
#define _VECTOR2D_H

namespace Vector2DUtil {

struct Vector2D {
    int8_t x;
    int8_t y;
};

Vector2D inline vectorAdd(Vector2D vec1, Vector2D vec2) {
    return Vector2D{(int8_t) (vec1.x + vec2.x), (int8_t) (vec1.y + vec2.y)};
}

Vector2D inline vectorSub(Vector2D vec1, Vector2D vec2) {
    return Vector2D{(int8_t) (vec1.x - vec2.x), (int8_t) (vec1.y - vec2.y)};
}

Vector2D inline scale(Vector2D vec, int8_t scalar) {
    return Vector2D{(int8_t) (vec.x * scalar), (int8_t) (vec.y * scalar)};
}

int8_t inline dotProduct(Vector2D vec1, Vector2D vec2) {
    return (vec1.x*vec2.x) + (vec1.y*vec2.y);
}

}

#endif /* _VECTOR2D_H */