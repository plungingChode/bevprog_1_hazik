#include <fstream>
#include <vector>
#include <iostream>

// 10. Add meg egy tetszőleges egész számsorról, hogy hány eleme nagyobb ill. kisebb az átlagánál.
int main()
{
    int n;
    std::cin >> n;

    int arr[n];

    double avg = 0;
    for (int i = 0; i < n; i++)
    {
         std::cin >> arr[i];
         avg += arr[i];
    }
    avg /= n;

    int kevesebb = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < avg) kevesebb++;
    }

    std::cout << kevesebb;
    return 0;
}
