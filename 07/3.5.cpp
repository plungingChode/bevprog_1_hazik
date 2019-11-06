#include <iostream>

// 3.5. Add meg két természetes szám legnagyobb közös osztóját.
int main()
{
    int szam1, szam2;
    std::cin >> szam1;
    std::cin >> szam2;

    int kozos = 1; // 1 ha mindig kozos
    int div = 2;
    while (div <= szam1 && div <= szam2)
    {
        if (szam1 % div == 0 && szam2 % div == 0)
        {
           kozos = div;
        }
        div++;
    }

    std::cout << kozos;
    return 0;
}
