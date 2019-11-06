#include <iostream>

// 3.4. Add meg egy természetes szám legnagyobb valódi osztóját.
int main()
{
    int szam;
    std::cin >> szam;

    int maximum = -1; // 1 es onmaga nem valodi oszto
    int div = 2;
    while (div < szam)
    {
        if (szam % div == 0)
        {
           maximum = div;
        }
        div++;
    }

    std::cout << maximum;
    return 0;
}
