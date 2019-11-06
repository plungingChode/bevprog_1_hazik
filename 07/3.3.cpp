#include <iostream>

// 3.3. Add meg egy tetszőleges egész szám valódi osztóinak a számát.
int main()
{
    int szam;
    std::cin >> szam;

    int db = 0; // 1 es onmaga nem valodi oszto
    int div = 2;
    while (div < szam)
    {
        if (szam % div == 0)
        {
            db++;
        }
        div++;
    }

    std::cout << db;
    return 0;
}
