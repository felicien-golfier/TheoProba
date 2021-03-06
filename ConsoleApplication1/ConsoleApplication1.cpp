// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <algorithm>
#include <list>

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
	//if (i.joker)
	//{
	//	if (j.joker)
	//		return i.number < j.number;
	//	else
	//		return true;
	//}
	//else 
	//{
	//	if (j.joker)
	//		return false;
	//	else if (i.number == j.number)
	//		if( i.color ! j.color)
	//	else
	//		return i.number < j.number;
	//}
	return i.joker ? j.joker ? i.number < j.number : true : j.joker ? false : i.number == j.number ? i.color==j.color? i.id < j.id : i.color == true : i.number < j.number;

}
struct Proba {

	uint64_t _nbIt = 0;
	uint64_t _suites[10][6][2] = {};
	uint64_t _nbIdentiques[8][6][2] = {};
	uint64_t _nbPairesImpraires[11] = {};
	uint64_t _nbCouleurs[11] = {};
	uint64_t _nbJoker[11][2] = {};

	void NouvelleMain(Carte nouvelleMain[10])
	{
		uint8_t nbCol = 0;
		uint8_t nbPair = 0;
		uint8_t nbJoker = 0;
		uint8_t nbJokerDry = 0;
		uint8_t suites[10][2] = {};
		uint8_t nbIdentiques[8][2] = {};
		uint8_t previousValue = 0;
		uint8_t previousSuiteSize = 0;
		uint8_t previousSuiteColorSize = 0;
		uint8_t previousSameSize = 0;
		uint8_t previousSameColorSize = 0;
		uint8_t previousJokerValues[10][2] = {};
		bool previousJokerUsed[10] = { false };
		uint8_t pJVI = 0;
		uint8_t suitesStillColor = 0;
		bool identiquesStillColor = true;

		//std::cout << "\n\nNeaw array ";
		//for (size_t i = 0; i != 10; ++i)
		//	std::cout << nouvelleMain[i].number << (nouvelleMain[i].joker ? "j":"")  << " ";
		std::sort(nouvelleMain, nouvelleMain + 10, WayToSort);
		bool previousColor = nouvelleMain[0].color;
		bool previousSuiteColor = nouvelleMain[0].color;
		//std::cout << "\n Sorted array ";

		//for (size_t i = 0; i != 10; ++i)
		//	std::cout << nouvelleMain[i].number << (nouvelleMain[i].joker ? "j" : "") << " ";
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


			if (c.joker)
			{
				previousJokerValues[pJVI][0] = c.number;
				previousJokerValues[pJVI++][1] = c.jokerNumber;
				continue;
			}

			if (c.number == previousValue)
			{
				//previousSameSize is initialized to 0. so all double will be store in the 0 field.
				
				nbIdentiques[previousSameSize][0]++;
				if (identiquesStillColor && c.color == previousColor)
					nbIdentiques[previousSameSize][1]++;
				else if (c.color == previousColor)
					nbIdentiques[previousSameColorSize++][1]++;
				else
					identiquesStillColor = false;
				
				previousSameSize++;
			}
			else if (previousValue > 0){
				//Add all the jokers !!
				for (int j = 0; j < pJVI; j++) {
					//If one of the joker has the same value, I add a previousSameValue and store the new.
					if (previousJokerValues[j][0] == previousValue || previousJokerValues[j][1] == previousValue)
					{
						nbIdentiques[previousSameSize][0]++;
						if (identiquesStillColor)
							nbIdentiques[previousSameSize][1]++;
						else {
							nbIdentiques[previousSameColorSize++][1]++;
						}
						previousSameSize++;
					}
				}

				switch (previousSameSize)
				{
				case 10:
					nbIdentiques[2][0]++;
					nbIdentiques[5][0]++;
				case 9:
					nbIdentiques[3][0]++;
				case 8:
					nbIdentiques[2][0]++;
					nbIdentiques[4][0]++;
				case 7:
				case 6:
					nbIdentiques[2][0]++;
					nbIdentiques[3][0]++;
				case 5:
				case 4:
					nbIdentiques[2][0]++;
				default:
					break;
				}
				switch (previousSameSize - previousSameColorSize)
				{
				case 10:
					nbIdentiques[2][1]++;
					nbIdentiques[5][1]++;
				case 9:
					nbIdentiques[3][1]++;
				case 8:
					nbIdentiques[2][1]++;
					nbIdentiques[4][1]++;
				case 7:
				case 6:
					nbIdentiques[2][1]++;
					nbIdentiques[3][1]++;
				case 5:
				case 4:
					nbIdentiques[2][1]++;
				default:
					break;
				}
				switch (previousSameColorSize)
				{
				case 10:
					nbIdentiques[2][1]++;
					nbIdentiques[5][1]++;
				case 9:
					nbIdentiques[3][1]++;
				case 8:
					nbIdentiques[2][1]++;
					nbIdentiques[4][1]++;
				case 7:
				case 6:
					nbIdentiques[2][1]++;
					nbIdentiques[3][1]++;
				case 5:
				case 4:
					nbIdentiques[2][1]++;
				default:
					break;
				}
				// Close that 
				previousSameSize = 0;
				previousSameColorSize = 0;
				identiquesStillColor = true;
			}


			//SUITES 

			// If the number is the same as the last, just check the color.
			if (c.number != previousValue)
			{
				if (c.number == previousValue + 1)
				{
					//If I found the next in this guy
					suites[previousSuiteSize][0]++;
					if (suitesStillColor == 0 && c.color == previousSuiteColor)
						suites[previousSuiteSize][1]++;
					else if (suitesStillColor == 0 && c.color != previousSuiteColor)
					{
						previousSuiteColorSize = previousSuiteSize;
						suitesStillColor = c.id;
					}

					previousSuiteSize++;
				}
				else {
					bool gotChain = false;
					bool hope = true;
					bool jokerFirstPlace = false;
					uint8_t hopeInJoker = 0;
					std::list<uint8_t*> jokers;
					while (hope)
					{
						gotChain = false;
						for (int j = 0; j < pJVI; j++) {
							if (!previousJokerUsed[j])
								jokers.push_back(previousJokerValues[j]);
							// Check if a joker could fit the nex number
							if (!previousJokerUsed[j] && (previousJokerValues[j][0] == previousValue + 1 || previousJokerValues[j][1] == previousValue + 1))
							{
								suites[previousSuiteSize][0]++;
								if (suitesStillColor == 0)
									suites[previousSuiteSize][1]++;

								previousSuiteSize++;
								previousJokerUsed[j] = true;
								gotChain = true;
								hopeInJoker++;
								break;
								//Check if a joker could fit the first place. But decide then to do something.
							}
							else if (!jokerFirstPlace 
								&& previousValue - previousSuiteSize -1 > 0
								&& !previousJokerUsed[j] 
								&& (previousJokerValues[j][0] == previousValue - previousSuiteSize - 1 || previousJokerValues[j][1] == previousValue - previousSuiteSize - 1))
							{
								jokerFirstPlace = true;
							}
						}	
						if (!gotChain)
						{
							//We can add a joker at the first place.
							if (jokerFirstPlace)
							{
								uint8_t firstSuiteValue = previousValue - previousSuiteSize - 1;
								
								for (uint8_t count = 0; count <= jokers.size() && !jokers.empty(); count++)
								{
									uint8_t* joker = jokers.front();
									jokers.pop_front();
									if (joker[0] == firstSuiteValue - 1)
									{
										suites[previousSuiteSize][0]++;
										if (suitesStillColor == 0)
											suites[previousSuiteSize][1]++;

										previousSuiteSize++;
										firstSuiteValue --;
										count = 0;
									}
									else if (joker[1] == firstSuiteValue - 1)
									{
										suites[previousSuiteSize][0]++;
										if (suitesStillColor == 0)
											suites[previousSuiteSize][1]++;

										previousSuiteSize++;
										firstSuiteValue--;
										count = 0;
									}
									else {
										jokers.push_back(joker);
									}
								}
							}
							// Reset suite. No joker can save you
							switch (previousSuiteSize)
							{
							case 10:
								suites[2][0]++;
								suites[5][0]++;
							case 9:
								suites[3][0]++;
							case 8:
								suites[2][0]++;
								suites[4][0]++;
							case 7:
							case 6:
								suites[2][0]++;
								suites[3][0]++;
							case 5:
							case 4:
								suites[2][0]++;
							default:
								break;
							}
							switch (previousSuiteColorSize)
							{
							case 10:
								suites[2][1]++;
								suites[5][1]++;
							case 9:
								suites[3][1]++;
							case 8:
								suites[2][1]++;
								suites[4][1]++;
							case 7:
							case 6:
								suites[2][1]++;
								suites[3][1]++;
							case 5:
							case 4:
								suites[2][1]++;
							default:
								break;
							}
							previousSuiteSize = 0;
							for (int k = 0; k < 10; k++)
							{
								previousJokerUsed[k] = false;
							}
							previousSuiteColorSize = 0;
							suitesStillColor = 0;
							hope = false;
						}
						else if (c.number == previousValue + 1 + hopeInJoker)
						{
							suites[previousSuiteSize][0]++;
							if (suitesStillColor == 0 && c.color == previousSuiteColor)
								suites[previousSuiteSize][1]++;
							else if (suitesStillColor == 0 && c.color != previousSuiteColor)
							{
								previousSuiteColorSize = previousSuiteSize;
								suitesStillColor = c.id;
							}
							previousSuiteSize++;
							break;
						}
					}
				}
				previousSuiteColor = c.color;
			}
			else {
				//Case of the previous miss color suite is not valid ! 
				if (previousSuiteSize > 0 && c.color != previousSuiteColor && suitesStillColor != 0)
				{
					// check every last cards if it failed at the prev or not.
					for (int j = i-1; j > 0; j--) {
						if (nouvelleMain[j].number == c.number) 
						{
							//If the previous card here is not the good one, then it failed before and just aboard the mission.
							if (nouvelleMain[j].id == suitesStillColor)
							{
								suitesStillColor = 0;
								previousSuiteColorSize = 0;
								previousSuiteColor = c.color;
								suites[previousSuiteSize-1][1]++;
									
								break;
							}
						}
						else
							break;
					}
				}
			}

			previousColor = c.color;
			previousValue = c.number;
		}

		this->_nbCouleurs[nbCol]++;
		this->_nbPairesImpraires[nbPair]++;

		this->_nbJoker[nbJoker][0]++;
		this->_nbJoker[nbJokerDry][1]++;

		for (int i = 0; i < 8; i++)
		{
			//Store in nbID[X][0] directly the number of at least 1 time.
			for (int j = 1; j <= nbIdentiques[i][0];j++)
				this->_nbIdentiques[i][j-1][0]++;
			
			for (int j = 1; j <= nbIdentiques[i][1];j++)
				this->_nbIdentiques[i][j-1][1]++;
		}

		for (int i = 0; i < 10; i++)
		{
			//Store in nbID[X][0] directly the number of at least 1 time.
			for (int j = 1; j <= suites[i][0]; j++)
				this->_suites[i][j - 1][0]++;

			for (int j = 1; j <= suites[i][1]; j++)
				this->_suites[i][j - 1][1]++;
		}
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
