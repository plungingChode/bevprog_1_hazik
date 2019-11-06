#include <iostream>
#include <fstream>

// 3.12. Egy tetszőleges számsorban add meg a legkisebb és a legnagyobb számot.
int main()
{
    std::fstream f("szamsor.txt");

    double min, max, n;
    if (f.good())
    {
        f >> n;
        min = n;
        max = n;
    }

    while (f.good())
    {
        f >> n;
        if (n < min) min = n;
        if (n > max) max = n;
    }

    std::cout << min << ' ' << max;
    f.close();
    return 0;
}
