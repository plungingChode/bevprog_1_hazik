#include <cmath>

// 6.13. Valósíts meg függvényt, ami kap három számot,
//       amik egy háromszög három oldalhossza, és megadja
//       a háromszög három magasságának hosszait
void magassagok(
    double a, double b, double c,
    double& ma, double& mb, double& mc)
{
    double s = (a + b + c) / 2;
    double terulet = std::sqrt(s * (s - a) * (s - b) * (s - c));

    // m(a) = 2 * T / a
    ma = 2 * terulet / a;
    mb = 2 * terulet / b;
    mc = 2 * terulet / c;
}