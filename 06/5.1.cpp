#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

// 5.1. V�letlen vektor: egy vektor elemeit t�ltsd fel v�letlensz�mokkal.
int main()
{
    std::srand(std::time(nullptr));
    std::vector<int> v(100);

    for (unsigned int i = 0; i < v.size(); i++)
    {
        v[i] = std::rand();
    }

    return 0;
}
