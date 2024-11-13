#pragma once
#include <fstream>

/// @brief Класс цвета
class Color {
public:
    double r{}; // красная компонента цвета
    double g{}; // зеленая компонента цвета
    double b{}; // синяя компонента цвета
    Color();
    Color(double inputRed, double inputGreen, double inputBlue);
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
};
