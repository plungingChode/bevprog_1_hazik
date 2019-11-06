#include <iostream>
#include <string>
#include <cctype>

// 3.22. Egy tetszőleges szövegről add meg, hány számjegy, hány nagybetű és hány kisbetű van benne.
int main()
{
    std::string str;
    std::getline(std::cin, str);

    int dbKis = 0;
    int dbNagy = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (std::islower(str[i])) dbKis++;
        if (std::isupper(str[i])) dbNagy++;
    }

    std::cout << dbKis << ' ' << dbNagy;
    return 0;
}
