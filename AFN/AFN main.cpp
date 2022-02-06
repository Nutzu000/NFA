#include <iostream>
#include "AFN.h"
int main()
{
	AFN a;
	a.citireFisier("Input.txt");
	std::cout << a;
	std::string cuvant;
	if (a.verificare()) {
		do {
			std::cout << "Introduceti un cuvant: ";
			std::cin >> cuvant;
			std::cout<<a.accepta(cuvant)<<std::endl;
		} while (cuvant != "?");
	}
	else {
		std::cout << "AFN-ul introdus nu este definit corect!\n";
	}
}