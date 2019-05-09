#include "lzw.h"
#include <iostream>


void usage(void)
{
    std::cout << "Usage: lzwtree in_file -o out_file" << std::endl;
}

int
main (int argc, char *argv[])
{

    if (argc != 4) {
        // ha nem annyit kapott a program, akkor felhomályosítjuk erről a júzetr:
        usage();
        // és jelezzük az operációs rendszer felé, hogy valami gáz volt...
        return -1;
    }

    // "Megjegyezzük" a bemenő fájl nevét
    char *inFile = *++argv;

    // a -o kapcsoló jön?
    if (*((*++argv)+1) != 'o')  {
        usage();
        return -2;
    }

    // ha igen, akkor az 5. előadásból kimásoljuk a fájlkezelés C++ változatát:
    std::fstream beFile (inFile, std::ios_base::in);
    std::fstream kiFile (*++argv, std::ios_base::out);

    unsigned char b; // ide olvassik majd a bejövő fájl bájtjait
    LZWBinFa binFa; // s nyomjuk majd be az LZW fa objektumunkba
        
    while (beFile.read ((char *) &b, sizeof (unsigned char))) {
        for (int i = 0; i < 8; ++i)
        {
	    // maszkolunk
            int egy_e = b & 0x80;
	    // csupa 0 lesz benne a végén pedig a vizsgált 0 vagy 1, az if megmondja melyik:
            if ((egy_e >> 7) == 1)
		// ha a vizsgált bit 1, akkor az '1' betűt nyomjuk az LZW fa objektumunkba
                binFa << '1';
            else
		// különben meg a '0' betűt:
                binFa << '0';
            b <<= 1;
        }

    }
    
    kiFile << binFa; // ehhez kell a globális operator<< túlterhelése, lásd fentebb
    // (jó ez az OO, mert mi ugye nem igazán erre gondoltunk, amikor írtuk, mégis megy, hurrá)

    kiFile  << "depth = " << binFa.getMelyseg () << std::endl;
    kiFile  << "mean = " << binFa.getAtlag () << std::endl;
    kiFile  << "var = " << binFa.getSzoras () << std::endl;

    binFa.szabadit ();

    kiFile.close();
    beFile.close();

    return 0;
}
