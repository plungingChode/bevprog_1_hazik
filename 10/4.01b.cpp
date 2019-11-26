#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// 4.1. Adott egy szövegfájl, ami egy recept hozzávalóit tartalmazza.
//      A fájl minden sora egy számmal kezdődik, ami egy összetevőből
//      szükséges mennyiség, majd vesszővel elválsztva tőle az összetevő neve jön.
//  b.) Add meg, hány olyan összetevő van, amiből kevesebb, mint egy egységnyi kell.
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

int egynel_kevesebb(const std::vector<Osszetevo>& osszetevok)
{
    int db = 0;
    for (const Osszetevo& o : osszetevok)
    {
        if (o.mennyiseg < 1) db++;
    }
    return db;
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
            std::cout << "Kevesebb, mint egy egyseg: " << egynel_kevesebb(osszetevok) << " db\n";
        }
    }
    else
    {
        std::cout << "A fajl nem erheto el\n";
    }

    return 0;
}
