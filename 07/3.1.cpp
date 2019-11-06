#include <iostream>

// 3.1. Van-e két egyforma elem a vektorban?
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
