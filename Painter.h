#pragma once
#include "Color.h"
#include "Point.h"
#include <memory>

class View;
class PainterImpl;

namespace sf {
    class RenderWindow;
}

class Painter {
  public:
    Painter(sf::RenderWindow& window, const View& view);
    ~Painter();
    void draw(const Point& center, double radius, const Color& color);
    void draw(const Point& topLeft, const Point& bottomRight, const Color& color);
  private:
    std::unique_ptr<PainterImpl> impl;
};