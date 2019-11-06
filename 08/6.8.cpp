#include <vector>
#include <iostream>

// 6.8. Valósítsd meg az int hany(vector<double> v, double ez) függvényt,
//      ami a paraméterül kapott vektorban megszámolja, hogy hány "ez" van benne
int hany(std::vector<double> v, double ez)
{
    double db = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i] == ez)
        {
            db++;
        }
    }
    return db;
}

int main()
{
    std::vector<double> v = {1, 1, 1, 2};
    std::cout << hany(v, 1);
    return 0;
}
