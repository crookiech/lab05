#include "Ball.hpp"
#include <cmath>

/// @brief Конструктор с параметрами
/// @param inputVelocity скорость мяча
/// @param inputCenter центр мяча
/// @param inputRadius радиус мяча
/// @param inputColor цвет мяча
/// @param isCollidableOrNot флаг о возможности мяча проходить сквозь другие объекты
Ball::Ball(Velocity inputVelocity, Point inputCenter, double inputRadius, Color inputColor, bool isCollidableOrNot)
    : BallVelocity(inputVelocity), BallCenter(inputCenter), BallRadius(inputRadius), BallColor(inputColor), isCollidable(isCollidableOrNot) {}

/// @brief Выполняет отрисовку мяча
/// @details объект Ball абстрагирован от способа отображения пикселей на экране, знаком с интерфейсом, который предоставляет Painter (выполняется путем вызова painter.draw(...))
/// @param painter контекст отрисовки
void Ball::drawBall(Painter& inputPainter) const {
    inputPainter.draw(BallCenter, BallRadius, BallColor);
}

/// @brief Задает координаты центра мяча
/// @param center центр мяча
void Ball::setBallCenter(const Point& inputCenter) {
    this->BallCenter = inputCenter;
}

/// @brief Задает скорость мяча
/// @param velocity значение скорости
void Ball::setBallVelocity(const Velocity& inputVelocity) {
    this->BallVelocity = inputVelocity;
}

/// @brief Возвращает флаг о возможности мяча проходить сквозь другие объекты
/// @return флаг о возможности мяча проходить сквозь другие объекты
bool Ball::getIsCollidable() const {
    return isCollidable;
}

/// @brief Возвращает координаты центра мяча
/// @return центр мяча
Point Ball::getBallCenter() const {
    return BallCenter;
}

/// @brief Возвращает радиус мяча
/// @return радиус мяча
double Ball::getBallRadius() const {
    return BallRadius;
}

/// @brief Возвращает массу мяча
/// @return масса мяча
double Ball::getBallMass() const {
    return M_PI * pow(BallRadius, 3) * 4. / 3.; // заданная формула
}

/// @brief Возваращает скорость мяча
/// @return скорость мяча
Velocity Ball::getBallVelocity() const {
    return BallVelocity;
}
