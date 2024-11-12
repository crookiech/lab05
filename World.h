#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include "Velocity.h"
#include "Physics.h"
#include <vector>
#include <string>

class Painter;

/// @brief Класс мира
class World {
public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void worldUpdate(double time);
private:
    Point topLeft; // верхняя левая граница мира
    Point bottomRight; // нижняя правая граница мира
    Physics physics; // объект физического движка
    std::vector<Ball> balls; // вектор с мячами
    std::vector<Dust> dusts; // вектор с частицами
    double restTime = 0.; // Длина отрезка времени, который не был учтен при прошлой симуляции
};
