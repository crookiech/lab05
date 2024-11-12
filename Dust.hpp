#pragma once
#include "Point.h"
#include "Color.h"
#include "Velocity.h"
#include "Painter.h"

/// @brief Класс частицы
class Dust {
private:
    Velocity DustVelocity; // скорость частицы
    Point DustCenter; // центр частицы
    double DustRadius; // радиус частицы
    Color DustColor; // цвет частицы
    double lifetime; // время жизни частицы
    bool isAlive = true; // флаг для отслеживания жизни частицы
public:
    Dust(Velocity inputVelocity, Point inputCenter, double inputRadius, Color inputColor, double inputLifetime);
    bool getIsAlive() const;
    void updateDust(double deltaTime);
    void setDustVelocity(const Velocity& inputVelocity);
    Velocity getDustVelocity() const;
    void drawDust(Painter& inputPainter) const;
    void setDustCenter(const Point& inputCenter);
    Point getDustCenter() const;
    double getDustRadius() const;
};