#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

/// @brief Класс, который реализует физические взаимодействия между шарами Ball и частицами пыли Dust внутри ограниченной области World Box
class Physics {
private:
    void collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const;
    void collideWithBox(std::vector<Ball>& balls, std::vector<Dust>& dusts) const;
    void moveBall(std::vector<Ball>& balls) const;
    void moveDust(std::vector<Dust>& dusts) const;
    void processCollision(Ball& a, Ball& b, double distanceBetweenCenters2) const;
    Point topLeft;
    Point bottomRight;
    double timePerTick;
public:
    Physics(double inputTimePerTick = 0.001);
    void setWorldBox(const Point& inputTopLeft, const Point& inputBottomRight);
    void physicsUpdate(std::vector<Ball>& balls, std::vector<Dust>& dusts, const size_t ticks) const;
};
