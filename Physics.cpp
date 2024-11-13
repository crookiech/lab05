#include "Physics.h"
#include <iostream>

/// @brief Функция вычисления скалярного произведения двух векторов
/// @param lhs координаты первого вектора
/// @param rhs координаты второго вектора
/// @return скалярное произведение двух векторов
double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

/// @brief Конструктор с параметрами
/// @param inputTimePerTick время, которое проходит за один шаг моделирования
Physics::Physics(double inputTimePerTick) : timePerTick{inputTimePerTick} {}

/// @brief Функция, которая задает границы области моделирования
/// @param inputTopLeft верхний левый угол границы 
/// @param inputBottomRight нижний правый угол границы
void Physics::setWorldBox(const Point& inputTopLeft, const Point& inputBottomRight) {
    this->topLeft = inputTopLeft;
    this->bottomRight = inputBottomRight;
}

/// @brief Функция перемещения мячей
/// @param balls вектор мячей
void Physics::moveBall(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) { // перебор всех мячей
        Point newPos = ball.getBallCenter() + ball.getBallVelocity().vector() * timePerTick; // новая позиция = текущая координата + вектор скорости * timePerTick
        ball.setBallCenter(newPos); // установление новой позиции мяча
    }
}

/// @brief Функция перемещения живых частиц
/// @param dusts вектор частиц
void Physics::moveDust(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) { // перебор всех частиц
        if (dust.getIsAlive()) { // если частица живая
            Point newPos = dust.getDustCenter() + dust.getDustVelocity().vector() * timePerTick;
            dust.setDustCenter(newPos); // установление новой позиции частицы
        }
    }
}

/// @brief Функция обновления состояний объектов
/// @param balls вектор мячей
/// @param dusts вектор частиц
/// @param ticks 
void Physics::physicsUpdate(std::vector<Ball>& balls, std::vector<Dust>& dusts, const size_t ticks) const {
    for (size_t i = 0; i < ticks; ++i) {
        moveBall(balls); // обновление позиции мячей
        moveDust(dusts); // обновление позиций частиц
        collideWithBox(balls, dusts); // обработка столкновений мячей с границами области
        collideBalls(balls, dusts); // обработка столкновений между мячами
    }
}

/// @brief Обработка столкновения между мячами
/// @param balls вектор мячей
/// @param dusts вектор частиц
void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (!a->isInsideWorld) continue; // Игнорируем мяч вне границ
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!b->isInsideWorld) continue; // Игнорируем мяч вне границ
            if (!a->getIsCollidable() && !b->getIsCollidable()) {continue;}
            const double distanceBetweenCenters2 = distance2(a->getBallCenter(), b->getBallCenter()); // квадрат расстояния между центрами шаров
            const double collisionDistance = a->getBallRadius() + b->getBallRadius(); // сумма радиусов
            const double collisionDistance2 = collisionDistance * collisionDistance;  // квадрат суммы радиусов
            if (distanceBetweenCenters2 < collisionDistance2) { // если расстояние между центрами мячей меньше суммы радиусов
                processCollision(*a, *b, distanceBetweenCenters2); // обработка столкновения мячей
                // Создание частиц при столкновении мячей
                for (int i = 0; i < 7; i++) {
                    double angle = (i * 2 * M_PI / 7); // разделяем угол на 7 частей
                    Velocity dustVelocity(100 * i, angle); // скорость частицы (у 7 частиц разные скорости)
                    Dust dust(dustVelocity, a->getBallCenter(), 10, Color(0, 1, 0), 0.15);
                    // Dust dust(dustVelocity, a->getBallCenter(), a->getBallRadius() / 5, Color(0, 1, 0), 0.15); // создание частицы зеленого цвета
                    dusts.push_back(dust); // добавление частицы в вектор частиц
                }
            }
        }
    }
}

/// @brief Обработка столкновения со стеной
/// @param balls вектор мячей
/// @param dusts вектор частиц
void Physics::collideWithBox(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (Ball& ball : balls) { // перебор всех мячей
        if (!ball.isInsideWorld) continue;
        const Point p = ball.getBallCenter(); //координаты центра мяча
        const double r = ball.getBallRadius(); // радиус мяча
        // Лямбда функция - определяет, находится ли мяч за пределами границ
        auto isOutOfRange = [](double centerCoordinate, double topLeftCoordinate, double bottomRightCoordinate) {
            return centerCoordinate < topLeftCoordinate || centerCoordinate > bottomRightCoordinate;
        };
        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) { // если координата x центра мяча вышла за пределы границ world box по горизонтали (с учетом радиуса мяча)
            Point vector = ball.getBallVelocity().vector(); // вектор скорости мяча
            vector.x = -vector.x; // меняем направление скорости мяча по оси x
            ball.setBallVelocity(vector); // устанавливаем новую скорость мяча
            // Создание частиц при столкновении со стеной
            for (int i = 0; i < 7; i++) {
                double angle = (i * 2 * M_PI / 7); // разделяем угол на 7 частей
                Velocity particleVelocity(100 * i, angle); // скорость частицы
                Dust dust(particleVelocity, p, 10, Color(1, 0, 0), 0.15);
                // Dust dust(particleVelocity, p, r / 5, Color(1, 0, 0), 0.15); // создание частицы красного цвета
                dusts.push_back(dust); // добавление частицы в вектор частиц
            }
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) { // если координата y центра мяча вышла за пределы границ world box по вертикали (с учетом радиуса мяча)
            Point vector = ball.getBallVelocity().vector(); // вектор скорости мяча
            vector.y = -vector.y; // меняем направление скорости мяча по оси y
            ball.setBallVelocity(vector); // устанавливаем новую скорость мяча
            // Создание частиц при столкновении со стеной
            for (int i = 0; i < 7; i++) {
                double angle = (i * 2 * M_PI / 7); // разделяем угол на 7 частей
                Velocity particleVelocity(100 * i, angle); // скорость частицы
                Dust dust(particleVelocity, p, 10, Color(1, 0, 0), 0.15);
                // Dust dust(particleVelocity, p, r / 5, Color(1, 0, 0), 0.15); // создание частицы красного цвета
                dusts.push_back(dust); // добавление частицы в вектор частиц
            }
        }
    }
}

/// @brief Процесс столкновения мячей
/// @param a ссылка на первый мяч
/// @param b ссылка на второй мяч
/// @param distanceBetweenCenters2 квадрат расстояния между центрами шаров
void Physics::processCollision(Ball& a, Ball& b, double distanceBetweenCenters2) const {
    const Point normal = (b.getBallCenter() - a.getBallCenter()) / std::sqrt(distanceBetweenCenters2); // нормированный вектор столкновения
    // получение скорости в векторном виде
    const Point aV = a.getBallVelocity().vector();
    const Point bV = b.getBallVelocity().vector();
    // коэффициент p учитывает скорость обоих мячей
    const double p = 2 * (dot(aV, normal) - dot(bV, normal)) / (a.getBallMass() + b.getBallMass());
    // задаем новые скорости мячей после столкновения
    a.setBallVelocity(Velocity(aV - normal * p * a.getBallMass()));
    b.setBallVelocity(Velocity(bV + normal * p * b.getBallMass()));
}
