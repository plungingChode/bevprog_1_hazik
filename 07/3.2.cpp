#include <iostream>

// 3.2. Add meg egy term�szetes sz�m oszt�inak �sszeg�t.
int main()
{
    int szam;
    std::cin >> szam;

    int ossz = 1; // 1 minden szam osztoja
    int div = 2;
    while (div <= szam)
    {
        if (szam % div == 0)
        {
            ossz += div;
        }
        div++;
    }

    std::cout << ossz;
    return 0;
}
