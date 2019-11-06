#include <vector>

// 6.6. Valósítsd meg a bool vane(vector<int> v, int ez) függvényt, ami
//      eldönti, hogy a paraméterül kapott vektor elemei között van-e "ez".
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