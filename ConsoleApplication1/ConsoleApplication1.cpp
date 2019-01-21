// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <conio.h>


struct Carte {

	int id = 0;
	int number = 0;
	// 2 colors, true for the first and false the second.
	bool color = false;
	bool joker = false;
	int jokerNumber = -1;
	Carte() {};
	Carte(int id)
	{
		this->id = id;
		if (id <= 80)
		{
			this->number = id % 10 == 0 ? 10 :id % 10; 
			this->color = (id <= 40);
			this->joker = false;
		}
		else if (id <= 90)
		{
			switch (id)
			{
			case 81:
				this->number = 1;
				this->joker = true;
				this->jokerNumber = 2;
				break;
			case 82:
				this->number = 3;
				this->joker = true;
				this->jokerNumber = 4;
				break;
			case 83:
				this->number = 5;
				this->joker = true;
				this->jokerNumber = 6;
				break;
			case 84:
				this->number = 7;
				this->joker = true;
				this->jokerNumber = 8;
				break;
			case 85:
				this->number = 9;
				this->joker = true;
				this->jokerNumber = 10;
				break;
			case 86:
				this->number = 1;
				this->joker = true;
				this->jokerNumber = 10;
				break;
			case 87:
				this->number = 2;
				this->joker = true;
				this->jokerNumber = 9;
				break;
			case 88:
				this->number = 3;
				this->joker = true;
				this->jokerNumber = 8;
				break;
			case 89:
				this->number = 4;
				this->joker = true;
				this->jokerNumber = 7;
				break;
			case 90:
				this->number = 5;
				this->joker = true;
				this->jokerNumber = 6;
				break;
			default:
				std::cout << "Not possible !!! " << id <<" !\n";

			}
		}
		else {
			this->joker = true;
			this->jokerNumber = 0;
		}
	}
};
bool WayToSort(Carte i, Carte j)
{
	return i.number < j.number;
}
struct Proba {
	uint32_t _nbIt = 0;
	uint32_t _suites[8][5][2] = {};
	uint32_t _nbIdentiques[5][5][2] = {};
	uint32_t _nbPaires[11] = {};
	uint32_t _nbCouleurs[11] = {};
	uint32_t _nbJoker[11][2] = {};

	void NouvelleMain(Carte nouvelleMain [10])
	{
		uint8_t nbCol = 0;
		uint8_t nbPair = 0;
		uint8_t nbJoker = 0;
		uint8_t nbJokerDry = 0;
		//std::cout << "\n\nNeaw array ";
		//for (size_t i = 0; i != 10; ++i)
		//	std::cout << nouvelleMain[i].number << " ";
		std::sort(nouvelleMain, nouvelleMain + 10, WayToSort);
		//std::cout << "\n Sorted array ";

		//for (size_t i = 0; i != 10; ++i)
		//	std::cout << nouvelleMain[i].number << " ";
		this->_nbIt++;
		for (int i = 0; i < 10; i++)
		{

			Carte c = nouvelleMain[i];
			// On compte le nombre de joker et on continue la boucle lors des 10 jokers sans valeures.
			if (c.joker)
			{
				nbJoker++;
				if (c.jokerNumber == 0) {
					nbJokerDry++;
					continue;
				}
			}

			// Compte le nombre de couleur et de pairs dans la main et on a compte chaque joker comme étant les deux.
			if (c.color || c.joker)
				nbCol++;
			if (c.joker || c.number%2==0)
				nbPair++;



		}

		_nbCouleurs[nbCol]++;
		_nbPaires[nbPair]++;

		_nbJoker[nbJoker][0]++;
		_nbJoker[nbJokerDry][1]++;
	}
};

int main()
{
    std::cout << "Hello World!\n"; 
	Carte cartes[10];
	Proba proba;
	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			int id;
			bool alreadyExist;
			do {
				alreadyExist = false;
				id = rand() % 100 + 1;
				for (int j = 0; j < i; j++)
				{
					if (cartes[j].id == id)
					{
						alreadyExist = true;
						break;
					}
				}
			} while (alreadyExist);
			cartes[i] = Carte(id);
			//std::cout << "Log cartes : id " << id << ", number " << cartes[i].number << ", joker " << cartes[i].joker << ", jokernumber " << cartes[i].jokerNumber << std::endl;
		}
		proba.NouvelleMain(cartes);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
