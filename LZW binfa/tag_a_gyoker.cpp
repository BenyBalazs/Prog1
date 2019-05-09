#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct binfa
{
  int ertek;
  struct binfa *bal_nulla;
  struct binfa *jobb_egy;

} BINFA, *BINFA_PTR;

BINFA_PTR
uj_elem ()
{
  BINFA_PTR p;

  if ((p = (BINFA_PTR) malloc (sizeof (BINFA))) == NULL)
    {
      perror ("memoria");
      exit (EXIT_FAILURE);
    }
  return p;
}

extern void kiir (BINFA_PTR elem);
extern void ratlag (BINFA_PTR elem);
extern void rszoras (BINFA_PTR elem);
extern void szabadit (BINFA_PTR elem);

int
main (int argc, char **argv)
{
  char b;

  BINFA_PTR gyoker = uj_elem ();
  gyoker->ertek = '/';
  gyoker->bal_nulla = gyoker->jobb_egy = NULL;
  BINFA_PTR fa = gyoker;

  while (read (0, (void *) &b, 1))
    {
      if (b == '0')
	{
	  if (fa->bal_nulla == NULL)
	    {
	      fa->bal_nulla = uj_elem ();
	      fa->bal_nulla->ertek = 0;
	      fa->bal_nulla->bal_nulla = fa->bal_nulla->jobb_egy = NULL;
	      fa = gyoker;
	    }
	  else
	    {
	      fa = fa->bal_nulla;
	    }
	}
      else
	{
	  if (fa->jobb_egy == NULL)
	    {
	      fa->jobb_egy = uj_elem ();
	      fa->jobb_egy->ertek = 1;
	      fa->jobb_egy->bal_nulla = fa->jobb_egy->jobb_egy = NULL;
	      fa = gyoker;
	    }
	  else
	    {
	      fa = fa->jobb_egy;
	    }
	}
    }

  printf ("\n");
  kiir (gyoker);
  
  extern int max_melyseg, atlagosszeg, melyseg, atlagdb;
  extern double szorasosszeg, atlag;

  printf ("melyseg=%d\n", max_melyseg-1);

  atlagosszeg = 0;
  melyseg = 0;
  atlagdb = 0;
  ratlag (gyoker);
  atlag = ((double)atlagosszeg) / atlagdb;

  atlagosszeg = 0;
  melyseg = 0;
  atlagdb = 0;
  szorasosszeg = 0.0;

  rszoras (gyoker);

  double szoras = 0.0;

  if (atlagdb - 1 > 0)
    szoras = sqrt( szorasosszeg / (atlagdb - 1));
  else
    szoras = sqrt (szorasosszeg);

  printf ("altag=%f\nszoras=%f\n", atlag, szoras);

  szabadit (gyoker);
}

int atlagosszeg = 0, melyseg = 0, atlagdb = 0;

void
ratlag (BINFA_PTR fa)
{

  if (fa != NULL)
    {
      ++melyseg;
      ratlag (fa->jobb_egy);
      ratlag (fa->bal_nulla);
      --melyseg;

      if (fa->jobb_egy == NULL && fa->bal_nulla == NULL)
	{

	  ++atlagdb;
	  atlagosszeg += melyseg;

	}

    }

}

double szorasosszeg = 0.0, atlag = 0.0;

void
rszoras (BINFA_PTR fa)
{

  if (fa != NULL)
    {
      ++melyseg;
      rszoras (fa->jobb_egy);
      rszoras (fa->bal_nulla);
      --melyseg;

      if (fa->jobb_egy == NULL && fa->bal_nulla == NULL)
	{

	  ++atlagdb;
	  szorasosszeg += ((melyseg - atlag) * (melyseg - atlag));

	}

    }

}

int max_melyseg = 0;

void
kiir (BINFA_PTR elem)
{
  if (elem != NULL)
    {
      ++melyseg;
      if (melyseg > max_melyseg)
	max_melyseg = melyseg;
      kiir (elem->jobb_egy);
      for (int i = 0; i < melyseg; ++i)
	printf ("---");
      printf ("%c(%d)\n", elem->ertek < 2 ? '0' + elem->ertek : elem->ertek,
	      melyseg-1);
      kiir (elem->bal_nulla);
      --melyseg;
    }
}

void
szabadit (BINFA_PTR elem)
{
  if (elem != NULL)
    {
      szabadit (elem->jobb_egy);
      szabadit (elem->bal_nulla);
      free (elem);
    }
}]]>
</programlisting>
A <filename>bin.txt</filename> szövegfájlban találhatunk egy bináris sort, ezt fogjuk a <filename>z.c</filename> fordításával és futtatásával bejárni.
<programlisting><![CDATA[
$ more bin.txt
00011101110
$ g++ z.c -o z
$ ./z <bin.txt
---------1(2)
------------0(3)
------1(1)
---/(0)
---------1(2)
------0(1)
---------0(2)
melyseg=3
altag=2.333333
szoras=0.577350]]></programlisting>
        </para>
    </section>        
        
    <section>
        <title>Fabejárás</title>
        <para>
            Járd be az előző (inorder bejárású) fát pre- és posztorder is!
        </para>
        <para>
            Megoldás forrása: <link xlink:href="https://gitlab.com/whoisZORZ/bhax/tree/master/attention_raising/Welch/Bejaras">https://gitlab.com/whoisZORZ/bhax/tree/master/attention_raising/Welch/Bejaras</link>
        </para>
        <para>
            Tanulságok, tapasztalatok, magyarázat...:
            Preorder bejáráskor először megvizsgáljuk, hogy üres-e a bejárandó fa.
Ha igen, akkor véget is ér az algoritmus.
Ha nem, akkor elhelyezzük a gyökérelemet a sor végére.
Ezután bejárjuk a gyökérelem bal oldali, majd jobb oldali részfáját preorder módon.
<programlisting><![CDATA[
$ more z_pre.c
void
kiir (BINFA_PTR elem)
{
  if (elem != NULL)
    {
      ++melyseg;
      if (melyseg > max_melyseg)
	    max_melyseg = melyseg;
      for (int i = 0; i < melyseg; ++i)
	    printf ("---");
      printf ("%c(%d)\n", elem->ertek < 2 ? '0' + elem->ertek : elem->ertek,
	      melyseg);
      kiir (elem->bal_nulla);
      kiir (elem->jobb_egy);
      --melyseg;
    }
}
$ gcc z_pre.c -o z_pre -lm
$ ./z_pre <bin.txt
---/(1)
------0(2)
---------0(3)
---------1(3)
------1(2)
---------1(3)
------------0(4)
melyseg=3
atlag=2.333333
szoras=0.577350]]>
</programlisting>
Postorder bejáráskor először (ha nem üres a bejárandó fa) járjuk be a gyökérelem bal oldali, majd jobb oldali részfáját postorder módon.
Ezután dolgozzuk fel a gyökérelemet, tehát helyezzük a sor végére.
<programlisting><![CDATA[
$ more z_post.c
void
kiir (BINFA_PTR elem)
{
  if (elem != NULL)
    {
      ++melyseg;
      if (melyseg > max_melyseg)
	    max_melyseg = melyseg;
      kiir (elem->bal_nulla);
      kiir (elem->jobb_egy);
      for (int i = 0; i < melyseg; ++i)
	    printf ("---");
      printf ("%c(%d)\n", elem->ertek < 2 ? '0' + elem->ertek : elem->ertek,
	      melyseg);
      --melyseg;
    }
}
$ gcc z_post.c -o z_post -lm
$ ./z_post <bin.txt
---------0(3)
---------1(3)
------0(2)
------------0(4)
---------1(3)
------1(2)
---/(1)
melyseg=3
atlag=2.333333
szoras=0.577350]]>
