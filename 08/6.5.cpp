#include <vector>

// 6.5. Valósítsd meg az int max(vector<int> v) függvényt, ami a paraméterül
//      kapott vektor elemei közül a legnagyobbat adja vissza
int max(std::vector<int> v)
{
    int max = v[0];
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }
    return max;
}