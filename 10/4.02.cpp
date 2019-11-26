#include <iostream>
#include <fstream>
#include <vector>

//4.2. Adott egy telefonkönyv egy szövegfájlban, aminek a sorai
//     vesszővel elválasztott neveket és telefonszámokat tartalmaznak.
//  a.) Egy tetszőleges névhez add meg a telefonszámot.
//  b.) Egy tetszőleges telefonszámhoz add meg a nevet.

struct Kontakt
{
    std::string nev;
    long long szam;

    friend std::ostream& operator<<(std::ostream& s, const Kontakt& k)
    {
        s << k.nev << ", " << k.szam;
        return s;
    }
};

void read_file(std::ifstream& f, std::vector<Kontakt>& v)
{
    while (f.good())
    {
        Kontakt k;
        f >> std::ws;
        std::getline(f, k.nev, ',');
        f >> k.szam >> std::ws;

        //std:: cout << k << '\n';
        v.push_back(k);
    }
}

long long nevhez_szam(std::vector<Kontakt>& tfkonyv, std::string nev)
{
    long long szam = -1;
    for (const Kontakt& k : tfkonyv)
    {
        if (k.nev == nev)
        {
            szam = k.szam;
            break;
        }
    }
    return szam;
}

std::string szamhoz_nev(std::vector<Kontakt>& tfkonyv, long long szam)
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
    std::vector<Kontakt> tfkonyv;
    read_file(f, tfkonyv);

    std::cout << nevhez_szam(tfkonyv, "Babosne Szigeti Ildiko") << std::endl;
    std::cout << szamhoz_nev(tfkonyv, 36302594766);

    return 0;
}
