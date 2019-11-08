#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>

// 5.3. Vektor szórása (átlagtól való eltérések átlaga)
int main()
{
    // random vektor
    std::srand(std::time(nullptr));
    std::vector<int> v(100);

    for (unsigned int i = 0; i < v.size(); i++)
    {
        v[i] = std::rand();
    }

    // atlag
    double avg = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        avg += v[i];
    }
    avg /= v.size();

    // szoras
    double szoras = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        szoras += std::abs(avg - v[i]);
    }
    szoras /= v.size();

    std::cout << szoras;

    return 0;
}
