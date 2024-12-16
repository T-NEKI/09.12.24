#include <iostream>
#include <cmath>
using namespace std;

// Функция для интегрирования
double f(double x) {
    return 1 + x * x;
}

// Метод прямоугольников
double rectangle_method(double a, double b, int n) {
    double h = (b - a) / n;                // Шаг разбиения
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        result += f(x);                    // Значение функции в левой границе
    }
    return result * h;                     // Умножение на шаг
}

// Метод трапеций
double trapezoid_method(double a, double b, int n) {
    double h = (b - a) / n;                // Шаг разбиения
    double result = 0.5 * (f(a) + f(b));   // Полусумма на концах
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        result += f(x);                    // Суммируем значения в промежуточных точках
    }
    return result * h;                     // Умножение на шаг
}

// Метод Симпсона
double simpson_method(double a, double b, int n) {
    if (n % 2 == 1) n++;                   // чётное число разбиений
    double h = (b - a) / n;                // Шаг разбиения
    double result = f(a) + f(b);           // Значение функции на концах
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            result += 2 * f(x);            // Умножение на 2 для чётных индексов
        }
        else {
            result += 4 * f(x);            // Умножение на 4 для нечётных индексов
        }
    }
    return result * h / 3;                 // Применение коэффициентов методики Симпсона
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Границы интегрирования
    double a = 0.0, b = 1.0;
    // Количество разбиений
    int n = 10;

    // Вычисления
    double rect_result = rectangle_method(a, b, n);
    double trap_result = trapezoid_method(a, b, n);
    double simp_result = simpson_method(a, b, n);

    // Точное значение интеграла для f(x) = 1 + x^2, [0, 1]: ∫(1 + x^2)dx = x + x^3 / 3
    double exact_result = (b + pow(b, 3) / 3) - (a + pow(a, 3) / 3);

    // Вывод результатов
    cout << "Метод прямоугольников: " << rect_result << endl;
    cout << "Метод трапеций: " << trap_result << endl;
    cout << "Метод Симпсона: " << simp_result << endl;
    cout << "Точное значение интеграла: " << exact_result << endl;

    // Абсолютные погрешности
    cout << "Погрешность метода прямоугольников: " << fabs(rect_result - exact_result) << endl;
    cout << "Погрешность метода трапеций: " << fabs(trap_result - exact_result) << endl;
    cout << "Погрешность метода Симпсона: " << fabs(simp_result - exact_result) << endl;

    return 0;
}
