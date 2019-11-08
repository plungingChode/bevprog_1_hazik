#include <iostream>

// 3.1. Számítsd ki egy szám faktoriálisát.
int main()
{
    int szam;
    std::cin >> szam;

    int faktor = 1;
    while (szam > 1)
    {
        faktor *= szam;
        szam -= 1;
    }

    std::cout << faktor;

    return 0;
}
