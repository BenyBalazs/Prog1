#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SZEL 78     // A programunk a SZEL szó helyére autómatikusan be fogja illesztenia 78 számot. Akkor jó, ha sok helyen használnánk ezt mert akkor nem fog kelleni mindenhol átjavítani ha esetleg gikszer van.
#define MAG 22

void putX(int x,int y) // 2 integerrel dolgozó funkció.
{
    int i; //Ciklusszámláló.

    for(i=0;i<x;i++) // Forciklus ami lefelé tolja a labdát. Addig megy amég az i nem érte el az x azaz a konzolablak magasságt, hogy ne menjen ki a kabda a képernyőről.
    printf("\n");

    for(i=0;i<y;i++) // Forciklus ami oldalirnyba tolja a labdát. Addig megy amég az i nem érte el az x azaz a konzolablak szélességét, hogy ne menjen ki a kabda a képernyőről.
    printf(" ");

    printf("X\n"); // Maga a labda.
}

int main()
{
    int x=0,y=0;

    while(1) //Végtelen ciklus ami írja a labdát.
{
    system("clear"); // Törli az eddig leírt labdákat, hogy ne csúfolja össze a képernyőt.
    putX(abs(MAG-(x++%(MAG*2))),abs(SZEL-(y++%(SZEL*2)))); // Meghívjuk a putX funkciónkat és felparaméterezzük. Abszolútértékbe helyezzük a műveleteket mert negatív képernyőhosszt azért nem szeretnénk kapni.
    usleep(50000); // Altatjuk egy kicsit a programunkat, hogy ne legyen villámgyors a labdapattogás.
}

    return 0;
}