#pragma once
#include "Point.h"
#include "Color.h"
#include "Velocity.h"
#include "Painter.h"

/// @brief Класс мяча
class Ball {
public:

    bool isInsideWorld; // Флаг для отслеживания положения мяча

    Ball(Velocity inputVelocity, Point inputCenter, double inputRadius, Color inputColor, bool isCollidableOrNot);
    bool getIsCollidable() const;
    void setBallVelocity(const Velocity& inputVelocity);
    Velocity getBallVelocity() const;
    void drawBall(Painter& painter) const;
    void setBallCenter(const Point& inputCenter);
    Point getBallCenter() const;
    double getBallRadius() const;
    double getBallMass() const;

private:
    Velocity BallVelocity; // скорость мяча
    Point BallCenter; // центр мяча
    double BallRadius; // радиус мяча
    Color BallColor; // цвет мяча
    bool isCollidable; // флаг о возможности мяча проходить сквозь другие объекты
};