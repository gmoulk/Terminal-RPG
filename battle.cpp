#include <iostream>
#include "Living.h"
using namespace std;

int battleEnd(Hero* team[], int sizeOfHeroTeam, Monster* monsterTeam[], int sizeOfMonsterTeam){
	int count = 0;
	for(int i = 0; i < sizeOfHeroTeam; i++){
		if(team[i]->getcurrentHealth() != 0)
			break;
		else
			count++;
		if(count == 3)
			return -1;			
	}
	
	count = 0;
	for(int i = 0; i < sizeOfMonsterTeam; i++){
		if(monsterTeam[i]->getHealth() != 0)
			break;
		else
			count++;
		if(count == 3)
			return 1;
	}
	
	return 0;
}

int battle(Hero* team[] , int sizeOfHeroTeam, Monster* monsterTeam[], int sizeOfMonsterTeam){
	int sideWin;
	do{
		for(int i = 0; i < sizeOfHeroTeam; i++){
			cout << "It is "<< team[i]->getName() << " turn would you like to:(1.Attack 2.Cast a spell 3.Use a potion 4.Change your armor or your weapon)" << endl;
			int option;
			cin >> option;
			switch(option){
				case 1:
					cout << "Choose an enemy to attack ";
					for(int j = 0; j < sizeOfMonsterTeam; j++)
						cout << j + 1 << ")" << monsterTeam[j]->getName() << " ";
					cout << endl;
					{
					bool legitOption = 0;
					int attackOption = 0;
					while(!legitOption){
						cin >> attackOption;
						if(attackOption > 0 && attackOption <= sizeOfMonsterTeam)
							legitOption = 1;
						else
							cout << "Your selection must be between " << 1 << " and " << sizeOfMonsterTeam << endl;	
					}
					int attackPoints = team[i]->attack();
					monsterTeam[option]->getAttacked(attackPoints);
					break;
					}
				case 2:
					cout << "Spell used" << endl;
					break;
				case 3:
					cout << "Potion used" << endl;
					break;
				case 4:
					cout << "Armor or weapons changed" << endl;					
			}
	}
	for(int i = 0; i < sizeOfMonsterTeam; i++){
		
	}
	}while((sideWin = battleEnd(team , sizeOfHeroTeam, monsterTeam, sizeOfMonsterTeam)));	

	return sideWin;
}
