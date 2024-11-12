#include "Dust.hpp"
#include <cmath>

/// @brief Конструктор с параметрами
/// @param inputVelocity скорость частицы
/// @param inputCenter центр частицы
/// @param inputRadius радиус частицы
/// @param inputColor цвет частицы
/// @param inputLifetime время жизни частицы
Dust::Dust(Velocity inputVelocity, Point inputCenter, double inputRadius, Color inputColor, double inputLifetime) 
: DustVelocity(inputVelocity), DustCenter(inputCenter), DustRadius(inputRadius), DustColor(inputColor), lifetime(inputLifetime) {}

/// @brief Обновление времени жизни частицы
/// @param deltaTime время, прошедшее с последнего обновления состояния частицы (в секундах)
void Dust::updateDust(double deltaTime) {
    lifetime -= deltaTime; // время жизни частицы сокращается на количество времени, прошедшее с последнего обновления
    if (lifetime <= 0) { // если частица умерла
        isAlive = false; // устанавливаем флаг для удаления
    }
}

/// @brief Выполняет отрисовку частицы
/// @details объект Dust абстрагирован от способа отображения пикселей на экране, знаком с интерфейсом, который предоставляет Painter (выполняется путем вызова painter.draw(...))
/// @param painter контекст отрисовки
void Dust::drawDust(Painter& inputPainter) const {
    inputPainter.draw(DustCenter, DustRadius, DustColor);
}

/// @brief Задает скорость частицы
/// @param velocity значение скорости
void Dust::setDustVelocity(const Velocity& inputVelocity) {
    this->DustVelocity = inputVelocity;
}

/// @brief Задает координаты центра частицы
/// @param center центр частицы
void Dust::setDustCenter(const Point& inputCenter) {
    this->DustCenter = inputCenter;
}

/// @brief Возваращает флаг отслеживания жизни частицы
/// @return 
bool Dust::getIsAlive() const {
    return isAlive;
}

/// @brief Возваращает скорость частицы
/// @return скорость частицы
Velocity Dust::getDustVelocity() const {
    return DustVelocity;
}

/// @brief Возвращает координаты центра частицы
/// @return центр частицы
Point Dust::getDustCenter() const {
    return DustCenter;
}

/// @brief Возвращает радиус частицы
/// @return радиус частицы
double Dust::getDustRadius() const {
    return DustRadius;
}
