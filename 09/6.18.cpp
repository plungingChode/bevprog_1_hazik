#include <vector>

// 6.18. Valósítsd meg a skalárszorzat műveletet függvényként
double skalarszorzat(std::vector<double> v1, std::vector<double> v2)
{
    double szorzat = 0;
    for (unsigned int i = 0; i < v1.size(); i++)
    {
        szorzat += v1[i] * v2[i];
    }
    return szorzat;
}
