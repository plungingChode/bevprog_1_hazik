#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

// 5.4. Van-e két egyforma elem a vektorban?
int main()
{
    // random vektor
    std::srand(std::time(nullptr));
    std::vector<int> v(100);

    for (unsigned int i = 0; i < v.size(); i++)
    {
        v[i] = std::rand();
    }

    bool vanEgyforma = false;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = 0; i < v.size(); i++)
        {
            if (i != j && v[i] == v[j])
            {
                vanEgyforma = true;
                break;
            }
        }

        if (vanEgyforma)
        {
            break;
        }
    }

    std::cout << vanEgyforma << std::endl;

    return 0;
}
