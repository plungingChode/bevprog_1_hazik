#include <sstream>

// 6.14. Val�s�ts meg f�ggv�nyt, amely egy sz�veget �talak�t �gy,
//       hogy ha t�bb whitespace karakter (sz�k�z, tab, �jsor) van
//       benne egym�s ut�n, azt egyetlen sz�k�zz� alak�tja
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