#include "Color.h"
#include <fstream>

/// @brief Конструктор по умолчанию
Color::Color() = default;

/// @brief Конструктор с параметрами
/// @param red красная компонента цвета
/// @param green зеленая компонента цвета
/// @param blue синяя компонента цвета
Color::Color(double inputRed, double inputGreen, double inputBlue) : r{inputRed}, g{inputGreen}, b{inputBlue} {}

/// @brief Возвращает значение красного компонента цвета
/// @return значение красной компоненты цвета
double Color::getRed() const {
    return r;
}

/// @brief Возвращает значение зеленого компонента цвета
/// @return значение зеленой компоненты цвета
double Color::getGreen() const {
    return g;
}

/// @brief Возвращает значение синего компонента цвета
/// @return значение синей компоненты цвета
double Color::getBlue() const {
    return b;
}
