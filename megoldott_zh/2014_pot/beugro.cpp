#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

#define ellenoriz(felt, pont) if (felt) pont++; else cerr << "Nem teljesul a feltetel a " << __LINE__<< ". sorban." <<endl;

/* Szabalyok:
    - csak az a beugr� �rv�nyes, amely nem tartalmaz semmilyen v�ltoztat�st a main()-ben,
        �s m�r nincs benne kommentezve semmi
    - az "ellenoriz"-en k�v�l nem tartalmaz #define sorokat, �s azt sem szabad megv�ltoztatni
*/

// Innentol

void szamjegyfelbont(int x, int& a, int& b)
{
    b = x % 10;
    a = (x - b) / 10;
}

struct S
{
    string s;
};

string pontok(int mennyi)
{
    string s = "";
    for (int i = 0; i < mennyi; i++)
    {
        s += '.';
    }
    return s;
}

bool vaneparatlan(vector<int>& v)
{
    for (const int& i : v)
    {
        if (i % 2 != 0)
        {
            return true;
        }
    }
    return false;
}

// Idaig

int main()
{
    int pont = 0;
    srand(time(0));

    int x = rand() % 100;
    int a,b;
    szamjegyfelbont(x,a,b);
    ellenoriz(10*a+b == x, pont)

    S s;
    s.s="s";
    ellenoriz(s.s=="s", pont)

    string s1 = pontok(4);
    string s2 = pontok(6);
    ellenoriz(s1=="...." && s2 == "......", pont)

    vector <int> v1;
    for (int i=0;i<10;i++) {
        v1.push_back(2*(rand()%10+4));
    }
    vector <int> v2;
    int index = rand()%10;
    for (int i=0;i<10;i++) {
        if (i!= index) {
            v2.push_back(2*(rand()%10+4));
        } else {
            v2.push_back(1+2*(rand()%10+4));
        }
    }
    ellenoriz(vaneparatlan(v1)==false && vaneparatlan(v2)==true, pont)

    cout << endl << pont << "/4 pont";
}
