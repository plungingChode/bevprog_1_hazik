#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

// 5.2. Vektor átlaga
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
    for (unsigned int i = 0; i < v.size(); i++) {
        avg += v[i];
    }
    avg /= v.size();

    std::cout << avg << std::endl;

    return 0;
}
