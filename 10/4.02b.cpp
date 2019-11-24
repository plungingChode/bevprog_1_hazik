#include <iostream>
#include <fstream>
#include <vector>

//4.2. Adott egy telefonkönyv egy szövegfájlban, aminek a sorai
//     vesszővel elválasztott neveket és telefonszámokat tartalmaznak.
//  b.) Egy tetszőleges telefonszámhoz add meg a nevet.

struct Kontakt
{
    long long szam;
    std::string nev;
};

std::vector<Kontakt> read_file(std::ifstream& f)
{
    std::vector<Kontakt> v;

    while(f.good())
    {
        std::string line;
        std::getline(f, line);

        unsigned int vesszo = line.find(',');

        Kontakt k;
        k.szam = std::stoll(line.substr(vesszo + 1));
        k.nev = line.substr(0, vesszo);

//        std::cout << k.szam << ',' << k.nev << '\n';

        v.push_back(k);
    }

    return v;
}

std::string szamot_keres(std::vector<Kontakt>& tfkonyv, long long szam)
{
    std::string nev = "Nincs ilyen szam";
    for (const Kontakt& k : tfkonyv)
    {
        if (k.szam == szam)
        {
            nev = k.nev;
            break;
        }
    }
    return nev;
}

int main()
{
    std::ifstream f("4.02.input.txt");
    std::vector<Kontakt> tfkonyv = read_file(f);

    std::cout << szamot_keres(tfkonyv, 36302594766) << std::endl;

    return 0;
}
