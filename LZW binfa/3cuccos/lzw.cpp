#include <iostream> // mert olvassuk a std::cin, írjuk a std::cout csatornákat
#include <cmath> // mert vonunk gyököt a szóráshoz: std::sqrt
#include <fstream> // fájlból olvasunk, írunk majd
#include "lzw.h"


void LZWBinFa::operator<<(char b)
    {
        // Mit kell betenni éppen, '0'-t?
        if (b == '0')
        {
            /* Van '0'-s gyermeke az aktuális csomópontnak?
             megkérdezzük Tőle, a "fa" mutató éppen reá mutat */
            if (!fa->nullasGyermek ()) // ha nincs, hát akkor csinálunk
            {
                // elkészítjük, azaz páldányosítunk a '0' betű akt. parammal
                Csomopont *uj = new Csomopont ('0');
                fa->ujNullasGyermek (uj);
                // és visszaállunk a gyökérre (mert ezt diktálja az alg.)
                fa = &gyoker;
            }
            else // ha van, arra rálépünk
            {
                // azaz a "fa" pointer már majd a szóban forgó gyermekre mutat:
                fa = fa->nullasGyermek ();
            }
        }
        // Mit kell betenni éppen, vagy '1'-et?
        else
        {
            if (!fa->egyesGyermek ())
            {
                Csomopont *uj = new Csomopont ('1');
                fa->ujEgyesGyermek (uj);
                fa = &gyoker;
            }
            else
            {
                fa = fa->egyesGyermek ();
            }
        }
    }

    void LZWBinFa::kiir (void)
    {

        melyseg = 0;
        // ha nem mondta meg a hívó az üzenetben, hogy hova írjuk ki a fát, akkor a
        // sztenderd out-ra nyomjuk
        kiir (&gyoker, std::cout);
    }
    void LZWBinFa::szabadit (void)
    {
        szabadit (gyoker.egyesGyermek());
        szabadit (gyoker.nullasGyermek());
        // magát a gyökeret nem szabadítjuk, hiszen azt nem mi foglaltuk a szabad tárban (halmon).
    }

        friend std::ostream& LZWBinFa::operator<< (std::ostream& os, LZWBinFa& bf)
    {
        bf.kiir(os);
        return os;
    }
    void LZWBinFa::kiir (std::ostream& os)
    {
        melyseg = 0;
        kiir (&gyoker, os);
    }