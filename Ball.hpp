#pragma once
#include "Point.h"
#include "Color.h"
#include "Velocity.h"
#include "Painter.h"

class Ball {
public:
    Ball(Velocity velocity, Point center, double radius, Color color, bool isCollidableOrNot);
    bool getIsCollidable() const;
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;

private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool isCollidable; // Новое поле
};