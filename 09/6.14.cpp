#include <sstream>

// 6.14. Valósíts meg függvényt, amely egy szöveget átalakít úgy,
//       hogy ha több whitespace karakter (szóköz, tab, újsor) van
//       benne egymás után, azt egyetlen szóközzé alakítja
std::string csak_egy_szokoz(std::string s)
{
    bool lehetSpace = true;
    std::stringstream retVal;
    for (const char c : s)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (lehetSpace)
            {
                retVal << ' ';
                lehetSpace = false;
            }
        }
        else
        {
            retVal << c;
            lehetSpace = true;
        }
    }
    return retVal.str();
}