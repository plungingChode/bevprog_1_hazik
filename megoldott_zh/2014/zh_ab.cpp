#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

struct Kozbeszerzes
{
    long id;
    std::string eljaras_cim;
    std::string ajanlatkero;
    std::string nyertes;
    unsigned long long ar;
    unsigned long long tag_ar;
    double cri;
    std::string url;
};

void read_file(std::ifstream& f, std::vector<Kozbeszerzes>& kbsz)
{
    const char delim = ';';
    char delim_sink;
    while (f.good())
    {
        f >> std::ws;
        
        Kozbeszerzes k;
        f >> k.id >> delim_sink;
        std::getline(f, k.eljaras_cim, delim);
        std::getline(f, k.ajanlatkero, delim);
        std::getline(f, k.nyertes, delim);
        f >> k.ar >> delim_sink;
        f >> k.tag_ar >> delim_sink;
        f >> k.cri >> delim_sink;
        std::getline(f, k.url);
        f >> std::ws;

        kbsz.push_back(k);
    }
}

// A csoport
int makulatlan(std::vector<Kozbeszerzes>& kbsz)
{
    std::set<std::string> tiszta;
    for (const Kozbeszerzes& k : kbsz)
    {
        if (k.cri == 0)
        {
            tiszta.insert(k.nyertes);
        }
    }
    return tiszta.size();
}

std::string legnagyobb_megrendelo(std::vector<Kozbeszerzes>& kbsz)
{
    unsigned long long max_ar = 0;
    std::string megrendelo;
    for (const Kozbeszerzes& k : kbsz)
    {
        if (k.ar > max_ar)
        {
            max_ar = k.ar;
            if (megrendelo != k.ajanlatkero)
            {
                megrendelo = k.ajanlatkero;
            }
        }
    }
    return megrendelo;
}

std::string viszonylag_tiszta(std::vector<Kozbeszerzes>& kbsz)
{
    std::map<std::string, 
             std::vector<double>> crik;

    for (const Kozbeszerzes k : kbsz)
    {
        if (k.cri != -1)
        {
            crik[k.nyertes].push_back(k.cri);
        }
    }

    int max_tiszta = 0;
    std::string legtisztabb;
    for (const std::pair<std::string, std::vector<double>>& pair : crik)
    {
        int db_tiszta = 0;
        for (const double cri : pair.second)
        {
            if (cri < 0.1) db_tiszta++;
        }

        if (db_tiszta > max_tiszta)
        {
            max_tiszta = db_tiszta;
            legtisztabb = pair.first;
        }
    }

    return legtisztabb;
}

// B csoport
// Ezt am nem tudom, hogy egyenkent szamit vagy atlagosan.
// Az alabbi megoldasban egyenkent nezem.
void kicsit_gyanus(std::vector<Kozbeszerzes>& kbsz)
{
    std::set<std::string> alig_gyanus;
    for (const Kozbeszerzes& k : kbsz)
    {
        if (k.cri < 0.05 && k.cri != -1)
        {
            alig_gyanus.insert(k.nyertes);
        }
    }

    for (const std::string& ny : alig_gyanus)
    {
        std::cout << "  * " << ny << '\n';
    }
}

void kicsit_gyanus_atlag(std::vector<Kozbeszerzes>& kbsz)
{
    std::map<std::string,
             std::vector<double>> crik;
    
    for (const Kozbeszerzes k : kbsz)
    {
        if (k.cri != -1)
        {
            crik[k.nyertes].push_back(k.cri);
        }
    }

    for (const std::pair<std::string, std::vector<double>>& pair : crik)
    {
        double cri_atlag = 0;
        for (const double cri : pair.second)
        {
            cri_atlag += cri;
        }
        cri_atlag /= pair.second.size();
        if (cri_atlag < 0.05)
        {
            std::cout << "  * " << pair.first << '\n';
        }
    }
}

int int32_nem_eleg(std::vector<Kozbeszerzes>& kbsz)
{
    int db = 0;
    for (const Kozbeszerzes& k : kbsz)
    {
        if (k.ar > INT32_MAX || k.tag_ar > INT32_MAX)
        {
            db++;
        }
    }
    return db;
}

int csak_egyszer(std::vector<Kozbeszerzes>& kbsz)
{
    std::map<std::string, int> ki_hanyszor;
    for (const Kozbeszerzes& k : kbsz)
    {
        ki_hanyszor[k.nyertes]++;
    }

    int egyszer = 0;
    for (const std::pair<std::string, int> p : ki_hanyszor)
    {
        if (p.second == 1) egyszer++;
    }

    return egyszer;
}


int main()
{
    std::vector<Kozbeszerzes> kbsz;
    std::ifstream f("budapest_kozbeszerzesek_szurt.txt");

    std::string header;
    std::getline(f, header);
    read_file(f, kbsz);
    f.close();

    std::cout << "\n=== A csoport ===\n";
    std::cout << "1.) Cegek, melyeknel volt CRI = 0: " 
              << makulatlan(kbsz) << " db\n";

    std::cout << "2.) A legnagyobb osszegu palyazat kiiroja: "
              << legnagyobb_megrendelo(kbsz) << '\n';

    std::cout << "3.) Viszonylag tiszta korulmenyek kozott legtobbszor nyert: "
              << viszonylag_tiszta(kbsz) << '\n';

    std::cout << "\n=== B csoport ===\n";
    std::cout << "1.a) Cegek, melyeknel volt CRI < 0.05:\n";
    kicsit_gyanus(kbsz);

    std::cout << "\n1.b) Cegek, melyeknel az atlagos CRI < 0.05:\n";
    kicsit_gyanus_atlag(kbsz);

    std::cout << "\n2.) Nem abrazolhato int32-kent: "
              << int32_nem_eleg(kbsz) << " db palyazat\n";

    std::cout << "3.) Csak egyszer nyert: "
              << csak_egyszer(kbsz) << " db ceg\n";

    return 0;
}