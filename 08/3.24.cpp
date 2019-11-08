#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// 3.24. Add meg egy tetszőleges szövegből a leghosszabb sort.
int main()
{
    int n;
    std::cin >> n;

    std::string max_str = "";
    std::string str;
    std::getline(std::cin, str); // egyet be kell olvasni csak ugy, mert a >> nem eszi meg az ujsor karaktert

    for (int i = 0; i < n; i++)
    {
        std::getline(std::cin, str);

        if (str.length() > max_str.length())
        {
            max_str = str;
        }
    }

    std::cout << max_str;
    return 0;
}
