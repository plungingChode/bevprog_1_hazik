#include <vector>

// 6.6. Val�s�tsd meg a bool vane(vector<int> v, int ez) f�ggv�nyt, ami
//      eld�nti, hogy a param�ter�l kapott vektor elemei k�z�tt van-e "ez".
bool vane(std::vector<int> v, int ez)
{
    bool van = false;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i] == ez)
        {
            van = true;
            break;
        }
    }
    return van;
}