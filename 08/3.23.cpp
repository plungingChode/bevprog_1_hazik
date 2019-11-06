#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// 3.23. Add meg egy tetszőleges szövegben, hogy melyik karakter fordul elő benne a legtöbbször.
int main()
{
    std::string str;
    std::getline(std::cin, str);

    std::vector<char> marVolt;
    char max_kar = ' ';
    int max_db = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        char c = str[i];
        bool volt = (std::count(marVolt.begin(), marVolt.end(), c) != 0);
        if (!volt)
        {
            marVolt.push_back(c);
            int db = std::count(str.begin(), str.end(), c);
            if (db > max_db)
            {
                max_db = db;
                max_kar = c;
            }
        }
    }

    std::cout << max_kar;
    return 0;
}
