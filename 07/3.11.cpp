#include <iostream>
#include <fstream>

// 3.11. Egy pozitív egész számokból álló számsorban add meg, hogy hány páros szám van.
int main()
{
    std::fstream f("szamsor.txt");

    int dbParos = 0;
    while (f.good())
    {
        int n;
        f >> n;
        if (n % 2 == 0)
        {
            dbParos++;
        }
    }

    std::cout << dbParos;
    f.close();
    return 0;
}
