#include "tp1.h"
#include <QApplication>
#include <time.h>

int isMandelbrot(Point z, int n, Point point) {
    // Cas de base : si n est égal à 0, alors la suite est bornée
    if (n == 0) {
        return 1;
    }

    // Calcul de z² + point
    double x_squared = z.x * z.x;
    double y_squared = z.y * z.y;
    double new_x = x_squared - y_squared + point.x;
    double new_y = 2 * z.x * z.y + point.y;

    // Si |z| > 2, alors la suite n'est pas bornée
    if (std::sqrt(x_squared + y_squared) > 2) {
        return n;
    }

    // Récursion avec n - 1 et le nouveau z
    return isMandelbrot(Point(new_x, new_y), n - 1, point);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



