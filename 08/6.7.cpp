#include <vector>

// 6.7. Valósítsd meg a double atlag(vector<double> v) függvényt,
//      ami a paraméterül kapott vektor átlagát adja vissza
double atlag(std::vector<double> v)
{
    double avg = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        avg += v[i];
    }
    avg /= v.size();
    return avg;
}
