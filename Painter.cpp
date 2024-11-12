#include "Painter.h"
#include "black_box/PainterImpl.h"
#include <SFML/Graphics/RenderWindow.hpp>

/// @brief Конструктор с параметрами
Painter::Painter(sf::RenderWindow& window, const View& view)
    : impl{new PainterImpl(window, view)} {} // инициализация уникального указателя impl, создавая новый объект PainterImpl, передавая ему ссылки на окно и вид

/// @brief Деструктор
Painter::~Painter() = default;

/// @brief Метод для рисования круга
/// @param center центр объекта
/// @param radius радиус объекта
/// @param color цвет объекта
void Painter::draw(const Point& center, double radius, const Color& color) {
    impl->draw(center, radius, color);
}

/// @brief метод для рисования прямоугольника
/// @param topLeft верхний левый угол объекта
/// @param bottomRight нижний правый угол объекта
/// @param color цвет объекта
void Painter::draw(const Point& topLeft, const Point& bottomRight, const Color& color) {
    impl->draw(topLeft, bottomRight, color);
}
