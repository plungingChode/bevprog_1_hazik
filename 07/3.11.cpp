#include <iostream>
#include <fstream>

// 3.11. Egy pozit�v eg�sz sz�mokb�l �ll� sz�msorban add meg, hogy h�ny p�ros sz�m van.
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
