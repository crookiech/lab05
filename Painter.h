#pragma once
#include "Color.h"
#include "Point.h"
#include <memory>

/// @brief Объявление классов из black_box
class View;
class PainterImpl;

/// @brief Объявление класса RenderWindow из пространства имен sf, которое принадлежит библиотеке SFML
namespace sf {
    class RenderWindow;
}

/// @brief Класс отрисовки объектов
class Painter {
private:
    std::unique_ptr<PainterImpl> impl; // std::unique_ptr обеспечивает автоматическое управление памятью
public:
    Painter(sf::RenderWindow& window, const View& view);
    ~Painter();
    void draw(const Point& center, double radius, const Color& color);
    void draw(const Point& topLeft, const Point& bottomRight, const Color& color);
};