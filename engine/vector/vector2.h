#include <cmath>
namespace engine::vector{
    struct Vector2{
        float x, y;
    };

    Vector2  operator+(Vector2 a, Vector2 b){
        return {a.x + b.x, b.y + a.y};
    }
    bool operator==(Vector2 a, Vector2 b){
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) <= 0.01;
    }

}