#include <iostream>

// 3.28 a. Egy több soros szövegben add meg, hány sorában található meg az "alma" szó.
//      b. Az "alma" helyett tetszőleges szöveget lehessen megadni.
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
        if (str.find(toFind) != std::string::npos)
        {
            cnt++;
        }
    }

    std::cout << cnt;
    return 0;
}
