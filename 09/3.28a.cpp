#include <iostream>

// 3.28 a. Egy t�bb soros sz�vegben add meg, h�ny sor�ban tal�lhat� meg az "alma" sz�.
int main()
{
    int n;
    std::cin >> n;

    int cnt = 0;
    std::string str;
    std::getline(std::cin, str);

    for (int i = 0; i < n; i++)
    {
        std::string str;
        std::getline(std::cin, str);
        if (str.find("alma") != std::string::npos)
        {
            cnt++;
        }
    }

    std::cout << cnt;
    return 0;
}
