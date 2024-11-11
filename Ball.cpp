#include "Ball.hpp"
#include <cmath>

Ball::Ball(Velocity velocity, Point center, double radius, Color color, bool isCollidableOrNot)
    : velocity(velocity), center(center), radius(radius), color(color), isCollidable(isCollidableOrNot) {}

bool Ball::getIsCollidable() const {
    return isCollidable; // Возвращаем значение поля
}

/// @brief Задает скорость объекта
/// @param velocity значение скорости
void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/// @brief Возваращает скорость объекта
/// @return скорость объекта
Velocity Ball::getVelocity() const {
    return velocity;
}

/// @brief Выполняет отрисовку объекта
/// @details объект Ball абстрагирован от способа отображения пикселей на экране, знаком с интерфейсом, который предоставляет Painter (выполняется путем вызова painter.draw(...))
/// @param painter контекст отрисовки
void Ball::draw(Painter& painter) const { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    painter.draw(center, radius, color);
}

/// @brief Задает координаты центра объекта
/// @param center центр объекта
void Ball::setCenter(const Point& center) {
    this->center = center;
}

/// @brief Возвращает координаты центра объекта
/// @return центр объекта
Point Ball::getCenter() const {
    return center;
}

/// @brief Возвращает радиус объекта
/// @return радиус объекта
double Ball::getRadius() const {
    return radius;
}

/// @brief Возвращает массу объекта
/// @return масса объекта
double Ball::getMass() const {
    return M_PI * pow(radius, 3) * 4. / 3.; // заданная формула
}
