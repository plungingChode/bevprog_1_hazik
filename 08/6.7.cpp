#include <vector>

// 6.7. Val�s�tsd meg a double atlag(vector<double> v) f�ggv�nyt,
//      ami a param�ter�l kapott vektor �tlag�t adja vissza
double atlag(std::vector<double> v)
{
    double avg = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        avg += v[i];
    }
    avg /= v.size();
    return avg;
}
