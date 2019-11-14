#include <iostream>

// 3.28 a. Egy több soros szövegben add meg, hány sorában található meg az "alma" szó.
//      b. Az "alma" helyett tetszőleges szöveget lehessen megadni.
//      c. A szó összes előfordulásának a számát add meg.
int main()
{
    std::string toFind;
    std::getline(std::cin, toFind);

    int n;
    std::cin >> n;

    int cnt = 0;
    std::string str;
    std::getline(std::cin, str);

    for (int i = 0; i < n; i++)
    {
        std::string str;
        std::getline(std::cin, str);

        unsigned int pos = str.find(toFind);
        while (pos != std::string::npos)
        {
            cnt++;
            pos = str.find(toFind, pos + toFind.length());
        }
    }

    std::cout << cnt;
    return 0;
}
