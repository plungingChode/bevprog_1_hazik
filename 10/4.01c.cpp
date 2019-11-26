#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// 4.1. Adott egy szövegfájl, ami egy recept hozzávalóit tartalmazza.
//      A fájl minden sora egy számmal kezdődik, ami egy összetevőből
//      szükséges mennyiség, majd vesszővel elválsztva tőle az összetevő neve jön.
//  c ) Add meg egy tetszőleges összetevőről, hogy mennyi kell belőle.
struct Osszetevo
{
    double mennyiseg;
    std::string nev;

    friend std::ostream& operator<<(std::ostream& s, const Osszetevo& o)
    {
        s << o.nev << ", " << o.mennyiseg;
        return s;
    }
};

void read_file(std::fstream& f, std::vector<Osszetevo>& v)
{
    char delim;
    while (f.good())
    {
        Osszetevo o;
        f >> std::ws >> o.mennyiseg >> delim >> std::ws;
        std::getline(f, o.nev);
        v.push_back(o);
    }
}

double mennyi(const std::vector<Osszetevo> osszetevok, std::string mi)
{
    for (const Osszetevo& o : osszetevok)
    {
        if (o.nev == mi) return o.mennyiseg;
    }
    return -1;
}

int main()
{
    std::fstream f("4.01.input.txt");
    if (f.good())
    {
        std::vector<Osszetevo> osszetevok;
        read_file(f, osszetevok);

        // for (const Osszetevo& o : osszetevok)
        // {
        //     std::cout << o << '\n';
        // }

        if (osszetevok.size() != 0)
        {
            std::string keres = "vanilias cukor";
            double ennyi = mennyi(osszetevok, keres);
            if (ennyi != -1)
            {
                std::cout << keres << ": " << ennyi << '\n';
            }
            else
            {
                std::cout << keres << " nincs a receptben\n";
            }
        }
    }
    else
    {
        std::cout << "A fajl nem erheto el\n";
    }

    return 0;
}
