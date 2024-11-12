#pragma once

/// @brief Класс цвета
class Color {
private:
    double r{}; // красная компонента цвета
    double g{}; // зеленая компонента цвета
    double b{}; // синяя компонента цвета
public:
    Color();
    Color(double inputRed, double inputGreen, double inputBlue);
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
};
