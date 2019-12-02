#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

#define ellenoriz(felt, pont) if (felt) pont++; else cerr << "Nem teljesul a feltetel a " << __LINE__<< ". sorban." <<endl;

/* Szabalyok:
    - csak az a beugro ervenyes, amely nem tartalmaz semmilyen valtoztatast a main()-ben,
        �s mar nincs benne kommentezve semmi
    - az "ellenoriz"-en kiv�l nem tartalmaz #define sorokat, es azt sem szabad megvaltoztatni
*/

// Innentol

vector<int> vektor3(int n0, int n1, int n2)
{
    vector<int> v(3);
    v[0] = n0;
    v[1] = n1;
    v[2] = n2;
    return v;
}

vector<int> osszeg(vector<int>& v1, vector<int>& v2)
{
    size_t sz = v1.size();
    if (v2.size() > sz) sz = v2.size();

    vector<int> sum(sz); 
    for (size_t i = 0; i < sz; i++)
    {
        sum[i] = v1[i] + v2[i];
    }

    return sum;
}

bool mindegyforma(vector<int>& v)
{
    bool egyforma = true;
    int ua = v[0];
    for (const int i : v)
    {
        if (ua != i)
        {
            egyforma = false;
            break;
        }
    }
    return egyforma;
}

struct ABC
{
    string keszlet;
};

bool vanbenne(ABC& abc, char c)
{
    return (abc.keszlet.find(c) != string::npos);
}

void unio(ABC& o1, ABC& o2)
{
    o1.keszlet += o2.keszlet;
}

// Idaig

int main() {
    int pont = 0;
    srand(time(0));

    vector<int> v1 = vektor3(1,2,3);
    vector<int> v2 = vektor3(6,5,4);
    ellenoriz(v1.size()==3 && v2.size()==3 && v1[0]==1 && v1[1]==2 && v1[2]==3 && v2[1]==5,pont)

    vector<int> vsum = osszeg(v1, v2);
    ellenoriz(vsum.size()==3 && vsum[0]==7 && vsum[1]==7 && vsum[2]==7,pont)

    ellenoriz(mindegyforma(vsum) && ! mindegyforma(v1),pont)

    ABC abc;
    abc.keszlet="abcd";
    ellenoriz(abc.keszlet=="abcd" && vanbenne(abc, 'a') && !vanbenne(abc, 'e'),pont)

    ABC abc2;
    abc2.keszlet="bcde";
    unio(abc, abc2);
    ellenoriz(vanbenne(abc, 'e') ,pont)

    cout << endl << pont << "/5 pont";
}
