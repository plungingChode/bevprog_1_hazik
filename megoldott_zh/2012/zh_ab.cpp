#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

struct Idopont
{
    int ora;
    int perc;
    int mp;
    std::string idozona;
};

struct Datum
{
    int ev;
    int honap;
    int nap;

    friend bool operator<(const Datum& lhs, const Datum& rhs)
    {
        return (lhs.ev < rhs.ev) ||
               (lhs.ev == rhs.ev && lhs.honap < rhs.honap) ||
               (lhs.ev == rhs.ev && lhs.honap == rhs.honap && lhs.nap < rhs.nap);
    }

    friend bool operator==(const Datum& d1, const Datum& d2)
    {
        return d1.ev == d2.ev && 
               d1.honap == d2.honap && 
               d1.nap == d2.nap;
    }
};

struct Latogatas
{
    Datum datum;
    Idopont ido;
    std::string ip_cim;
    std::string referrer;
};

void read_file(std::ifstream& f, std::vector<Latogatas>& v)
{
    char delim_sink;
    while (f.good())
    {
        Latogatas l;
        f >> l.datum.ev >> delim_sink;
        f >> l.datum.honap >> delim_sink;
        f >> l.datum.nap >> std::ws;
        f >> l.ido.ora >> delim_sink;
        f >> l.ido.perc >> delim_sink;
        f >> l.ido.mp >> std::ws >> delim_sink;
        std::getline(f, l.ido.idozona, ')');
        f >> std::ws;
        std::getline(f, l.ip_cim, ' ');
        std::getline(f, l.referrer);

        f >> std::ws;
        v.push_back(l);
    }
}

float napkozben_arany(std::vector<Latogatas>& v)
{
    // napkozben == 8 - 19 ora kozott
    int db = 0;
    for (const Latogatas& l : v)
    {
        if (l.ido.ora >= 8 && l.ido.ora <= 19)
        {
            db++;
        }
    }
    return db / (float)v.size();
}

std::string sokszor_ugyanaz(std::vector<Latogatas>& v)
{
    int abs_max = 0;
    std::string abs_max_cim;

    int loc_max = 0;
    std::string loc_max_cim = v[0].ip_cim;

    for (const Latogatas& l : v)
    {
        if (l.ip_cim == loc_max_cim)
        {
            loc_max++;
        }
        else
        {
            if (loc_max > abs_max)
            {
                abs_max = loc_max;
                abs_max_cim = loc_max_cim;
                // std::cout << abs_max << '\n';
            }
            
            loc_max = 0;
            loc_max_cim = l.ip_cim;
        }         
    }

    return abs_max_cim;
}

std::string get_qterm(std::string referrer)
{
    std::string qterm = "";

    size_t q = referrer.find("q=") + 2;
    size_t end = referrer.find('&', q);
    if (q != std::string::npos && 
        end != std::string::npos)
    {
        qterm = referrer.substr(q, end - q);    
    }

    return qterm;
}

std::string gyakori_keresoszo(std::vector<Latogatas>& v)
{
    std::map<std::string, int> szavak;
    for (const Latogatas& l : v)
    {
        if (l.referrer != "direct") 
        {
            std::string kereso = get_qterm(l.referrer);
            if (kereso.length() != 0)
            {
                szavak[kereso]++;
            }
        }
    }

    int max_db = 0;
    std::string max_szo = "";
    for (const std::pair<std::string, int>& p : szavak)
    {
        if (p.second > max_db)
        {
            // std::cout << p.first << '=' << p.second << '\n';
            max_db = p.second;
            max_szo = p.first;
        }
    }
    
    return max_szo + " [" + std::to_string(max_db) + " talalat]" ;
}

// B csoport
void print_idoszak(std::vector<Latogatas>& v)
{
   float oszi = 0;
   float nyari = 0;
   float tavaszi = 0;
   for (const Latogatas& l : v)
   {
       int honap = l.datum.honap;
       if (honap >= 7 && honap <= 8)
       {
           nyari++;
       }
       else if (honap >= 2 && honap <= 6)
       {
           tavaszi++;
       }
       else 
       {
           oszi++;
       }
   }

   oszi /= v.size();
   nyari /= v.size();
   tavaszi /= v.size();

   std::cout << "  * osz: " << oszi * 100 << "%\n"
             << "  * tavasz: " << tavaszi * 100 << "%\n"
             << "  * nyar: " << nyari * 100 << "%\n";
}

std::string legnepszerubb_11(std::vector<Latogatas>& v)
{
    std::map<Datum, int> napi_lat;
    for (const Latogatas& l : v)
    {
        if (l.datum.ev == 2011)
        {
            napi_lat[l.datum]++;
        }
    }

    Datum max_nap;
    int max_db;
    for (const std::pair<Datum, int>& p : napi_lat)
    {
        if (p.second > max_db)
        {
            // std::cout << p.first.ev << '.' << p.first.honap << '.' << p.first.nap << '=' << p.second << '\n';
            max_db = p.second;
            max_nap = p.first;
        }
    }

    return std::to_string(max_nap.honap) + '.' + std::to_string(max_nap.nap);
}

std::string max_direkt_letolt(std::vector<Latogatas>& v)
{
    std::map<std::string, int> direkt;
    for (const Latogatas& l : v)
    {
        if (l.referrer == "direct")
        {
            direkt[l.ip_cim]++;
        }
    }

    std::string max_ip;
    int max_db;
    for (const std::pair<std::string, int>& p : direkt)
    {
        if (p.second > max_db)
        {
            max_db = p.second;
            max_ip = p.first;
        }
    }

    return max_ip + " [" + std::to_string(max_db) + " letoltes]" ;
}

int main()
{
    std::ifstream f("netlog.txt");
    std::vector<Latogatas> latogatok;
    read_file(f, latogatok);
    f.close();

    // std::cout << latogatok[0].ip_cim << '\n';
    // std::cout << latogatok[0].ido.idozona << '\n';
    // std::cout << latogatok[0].referrer << '\n';

    std::cout << "\n=== A csoport ===\n";
    std::cout << "1.) Napkozbeni lekeresek: " 
              << napkozben_arany(latogatok) * 100 << "%\n";

    std::cout << "2.) Legtobbszor egymas utan letoltotte: "
              << sokszor_ugyanaz(latogatok) << '\n';

    std::cout << "3.) Leggyakoribb keresoszo: "
              << gyakori_keresoszo(latogatok) << '\n';

    std::cout << "\n=== B csoport ===\n";
    std::cout << "1.) Idoszakonkenti letoltesek:\n";
    print_idoszak(latogatok);

    std::cout << "2.) Legnepszerubb nap 2011-ben: "
              << legnepszerubb_11(latogatok) << '\n';

    std::cout << "3.) Legtobbszor direkt letoltotte: "
              << max_direkt_letolt(latogatok) << '\n';

    return 0;
}