#include <vector>

// 6.5. Val�s�tsd meg az int max(vector<int> v) f�ggv�nyt, ami a param�ter�l
//      kapott vektor elemei k�z�l a legnagyobbat adja vissza
int max(std::vector<int> v)
{
    int max = v[0];
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }
    return max;
}