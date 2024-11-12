#include "World.h"
#include "Painter.h"
#include <fstream>
#include "algorithm"

// Изменять не следует
static constexpr double timePerTick = 0.001; // время одного тика в секундах

/// @brief Функция считывания координат точки
/// @param stream входящий поток
/// @return точку
Point readPoint(std::istream& stream) {
    double x, y; // координаты точки
    stream >> x >> y; // считывание x и y из потока stream
    return Point(x, y); // создание точки с координатами x и y
}

/// @brief Функция считывания компонент цвета
/// @param stream входящий поток
/// @return цвет
Color readColor(std::istream& stream) {
    double red, green, blue; // компоненты цвета
    stream >> red >> green >> blue; // считывание
    return Color(red, green, blue); // создание
}

/// @brief Конструирует объект мира для симуляции
/// @param worldFilePath путь к файлу модели мира
World::World(const std::string& worldFilePath) {
    std::ifstream stream(worldFilePath); // объект ifstream для чтения из файла, заданного в worldFilePath
    topLeft = readPoint(stream); // считывание координат верхнего левого угла мира
    bottomRight = readPoint(stream); // считывание координат нижнего правого угла мира
    physics.setWorldBox(topLeft, bottomRight); // установление границ мира
    double radius; // радиус мяча
    bool isCollidable; // информация о возможности столкновения мяча
    while (stream.peek(), stream.good()) { // цикл, который читает информацию из файла до конца файла
        Point center = readPoint(stream); // считывание координат центра мяча
        Point vector = readPoint(stream); // считывание вектора скорости мяча
        Velocity velocity(vector); // сохдание скорости мяча
        Color color = readColor(stream); // считывание цвета мяча
        stream >> radius; // считывание радиуса мяча
        stream >> std::boolalpha >> isCollidable; // считывание isCollidable
        Ball ball(velocity, center, radius, color,isCollidable); // создание объекта Ball
        balls.push_back(ball); // добавление мяча в вектор
    }
}

/// @brief Отображение мира
/// @param painter 
void World::show(Painter& painter) const {
    painter.draw(topLeft, bottomRight, Color(1, 1, 1)); // отрисовка фона белого цвета
    // Отрисовка мячей
    for (const Ball& ball : balls) {
        ball.drawBall(painter);
    }
    // Отрисовка частиц
    for (const Dust& dust : dusts) {
        if (dust.getIsAlive()) { // если частица жива
            dust.drawDust(painter);
        }
    }
}

/// @brief Обновление состояния мира
/// @param time 
void World::worldUpdate(double time) {
    time += restTime; // restTime - остаток времени от предыдущего тика
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick)); // количество тиков, прошедших за заданное время time с учетом timePerTick
    restTime = time - double(ticks) * timePerTick; // обновление restTime, хранящий остаток времени после вычисления тиков
    physics.physicsUpdate(balls, dusts, ticks); // обновление физики для мячей и частиц
    // Обновление состояния частиц
    for (auto& dust : dusts) {
        dust.updateDust(timePerTick); // передача времени для обновления частиц
    }
    // Удаление мертвых частиц
    dusts.erase(std::remove_if(dusts.begin(), dusts.end(), [](const Dust& dust) {
        return !dust.getIsAlive();
    }), dusts.end()); // использование алгоритма remove_if, чтобы удалить мертвые частицы из вектора dusts
}
