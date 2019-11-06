#include <iostream>
#include <string>

// 3.21. Egy tetszőleges szövegről add meg, hány kis "a" betű van benne.
int main()
{
    std::string str;
    std::getline(std::cin, str);

    int db = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'a') db++;
    }

    std::cout << db;
    return 0;
}
