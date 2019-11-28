#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

struct Koordinata
{
    int fok;
    int szogperc;
    int szogmp;
    char felteke;

public:
    void szovegbol_feltolt(std::string str)
    {
        size_t vege = str.length() - 1;
        felteke = str[vege];
        szogmp = std::stoi(str.substr(vege - 2, 2));
        szogperc = std::stoi(str.substr(vege - 4, 2));
        fok = std::stoi(str.substr(0, vege - 4));
    }

    long masodpercben() const
    {
        return fok * 3600 + szogperc * 60 + szogmp;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Koordinata& k)
    {
        stream << k.felteke << ' ' << k.fok << " fok " 
               << k.szogperc << "' " << k.szogmp << "''";
        
        return stream;
    }
};

struct Repter
{
    std::string nev;
    std::string megye;
    std::string allam;
    Koordinata szelesseg;
    Koordinata hosszusag;
    int magassag; // lab

    friend std::ostream& operator<<(std::ostream& stream, const Repter& r)
    {
        stream << r.nev << ", " << r.megye << " [" << r.allam << "] - {"
               << r.szelesseg << "} : {" << r.hosszusag << "}, " << r.magassag;
        
        return stream;
    }

};

void read_file(std::ifstream& f, std::vector<Repter>& v)
{
    const char delim = '|';
    char delim_sink;
    while (f.good())
    {
        Repter r;
        std::getline(f, r.nev, delim);
        std::getline(f, r.megye, delim);
        std::getline(f, r.allam, delim);

        std::string koord;
        std::getline(f, koord, delim);
        r.szelesseg.szovegbol_feltolt(koord);

        std::getline(f, koord, delim);
        r.hosszusag.szovegbol_feltolt(koord);

        f >> r.magassag >> std::ws;

        v.push_back(r);
    }
}

// A csoport
int helikopternek(std::vector<Repter>& v)
{
    std::string heli[] = {"Helipad", "Heliport", "Helistop"};

    int db = 0;
    for (const Repter& r : v)
    {
        for (const std::string h : heli)
        {
            if (r.nev.find(h) != std::string::npos)
            {
                db++; 
                break;
            }
        }
    }

    return db;
}

std::string tx_max_magassag(std::vector<Repter>& v)
{
    std::string magas;
    int max_magassag = -9999;
    for (const Repter& r : v)
    {
        if (r.allam == "TX" && r.magassag > max_magassag)
        {
            max_magassag = r.magassag;
            magas = r.nev;
        }
    }
    return magas;
}

double tavolsag(const Repter& r1, const Repter& r2)
{
    long x1 = r1.hosszusag.masodpercben();
    long y1 = r1.szelesseg.masodpercben();

    long x2 = r2.hosszusag.masodpercben();
    long y2 = r2.szelesseg.masodpercben();

    double x = std::pow(x1 - x2, 2);
    double y = std::pow(y1 - y2, 2);

    return std::sqrt(x + y);
}

void print_eny_tavoli(const std::vector<Repter>& v)
{
    // ez amugy majdnem az osszes
    std::vector<Repter> csak_eny;
    for (const Repter& r : v)
    {
        if (r.szelesseg.felteke == 'N' &&
            r.hosszusag.felteke == 'W')
        {
            csak_eny.push_back(r);
        }
    }

    Repter tavol1, tavol2;
    double max_tavolsag = 0;
    size_t hatar = csak_eny.size() / 2;
    for (const Repter& r2 : csak_eny)
    {
        for (const Repter& r1 : csak_eny)
        {
            double tav = tavolsag(r1, r2);
            if (tav > max_tavolsag)
            {
                max_tavolsag = tav;
                tavol1 = r1;
                tavol2 = r2;
            }
        }
    }

    std::cout << "  * " << tavol1 << '\n'
              << "  * " << tavol2 << '\n';
}

// B csopoort
int nem_airport(std::vector<Repter>& v)
{
    int db = 0;
    for (const Repter& r : v)
    {
        if (r.nev.find("Airport") == std::string::npos)
        {
            db++;
        }
    }
    return db;
}

double ca_avg_magassag(std::vector<Repter>& v)
{
    long ossz_magassag = 0;
    int repterek = 0;
    for (const Repter& r : v)
    {
        if (r.allam == "CA")
        {
            ossz_magassag += r.magassag;
            repterek++;
        }
    }
    return ossz_magassag / (float)repterek;
}

void print_legkozelebbi(std::vector<Repter>& v)
{
    Repter kozel1, kozel2;
    double legkozelebb = tavolsag(v[0], v[1]);
    for (const Repter& r1 : v)
    {
        for (const Repter& r2 : v)
        {
            double tav = tavolsag(r1, r2);
            if (tav != 0 && tav < legkozelebb)
            {
                legkozelebb = tav;
                kozel1 = r1;
                kozel2 = r2;
            }
        }
    }
    std::cout << "  * " << kozel1 << '\n'
              << "  * " << kozel2 << '\n';
}

int main()
{
    std::ifstream f("repterek.txt");
    std::vector<Repter> repterek;
    read_file(f, repterek);
    f.close();

    // std::cout << repterek.size() << '\n';

    std::cout << "\n=== A csoport ===\n"; 
    std::cout << "1.) Szerepel a neveben 'Helipad', 'Heliport', vagy 'Helistop': " 
              << helikopternek(repterek) << " db\n";

    std::cout << "2.) Texas allam legmagasabb reptere: "
              << tx_max_magassag(repterek) << '\n';

    std::cout << "3.) Eszaknyugaton a ket legtavolabbi repter (ez kb. 5 perc, amig lefut):\n";
    print_eny_tavoli(repterek);

    std::cout << "\n=== B csoport ===\n";
    std::cout << "1.) Nem szerepel a neveben 'Airport': "
              << nem_airport(repterek) << " db\n";

    std::cout << "2.) California allam reptereinek atlagos magassaga: "
              << ca_avg_magassag(repterek) << '\n';
    
    std::cout << "3.) A ket legkozelebbi repter (ez is par perc lesz):\n";
    print_legkozelebbi(repterek);

    return 0;
}