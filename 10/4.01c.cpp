#include <iostream>
#include <fstream>
#include <vector>

// 4.1. Adott egy szövegfájl, ami egy recept hozzávalóit tartalmazza.
//      A fájl minden sora egy számmal kezdődik, ami egy összetevőből
//      szükséges mennyiség, majd vesszővel elválsztva tőle az összetevő neve jön.
//  c ) Add meg egy tetszőleges összetevőről, hogy mennyi kell belőle.

struct Osszetevo
{
    double mennyiseg;
    std::string nev;
};

std::vector<Osszetevo> read_file(std::fstream& f)
{
    std::vector<Osszetevo> v;
    while (f.good())
    {

        std::string line;
        std::getline(f, line);
        unsigned int vesszo = line.find(',');

        Osszetevo o;
        o.mennyiseg = std::stod(line.substr(0, vesszo));
        o.nev = line.substr(vesszo + 1);
//        std::cout << o.mennyiseg << ',' << o.nev << '\n';

        v.push_back(o);
    }
    return v;
}

void mennyi(const std::vector<Osszetevo>& osszetevok, std::string mi)
{
    for (const Osszetevo& o : osszetevok)
    {
        if (o.nev == mi)
        {
            std::cout << mi << ": " << o.mennyiseg << '\n';
            return;
        }
    }
    std::cout << mi << " nincs a receptben\n";
}

int main()
{
    std::fstream f("4.1.input.txt");
    if (f.good())
    {
        std::vector<Osszetevo> osszetevok = read_file(f);
        if (osszetevok.size() != 0)
        {
            mennyi(osszetevok, "liszt");
        }
    }
    else
    {
        std::cout << "A fajl nem erheto el\n";
    }

    return 0;
}
