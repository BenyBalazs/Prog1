#include <iostream>

int main()
{
    int a = 0;
	std::cout << "Adj meg egy termeszetes szamot amit atvaltunk: ";
	std::cin >> a ;
	std::cout << "\n";
	if(a >0)
	{
        for(int i = 0;i<a;++i)
        {
            std::cout << "|";
        }
	}
	else
        std::cout << "A megadott szam nem megfelelo.";
	std::cout << "\n";
	return 0;
}
