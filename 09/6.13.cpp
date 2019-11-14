#include <cmath>

// 6.13. Val�s�ts meg f�ggv�nyt, ami kap h�rom sz�mot,
//       amik egy h�romsz�g h�rom oldalhossza, �s megadja
//       a h�romsz�g h�rom magass�g�nak hosszait
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