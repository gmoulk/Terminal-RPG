//#include <iostream>
//#include "Living.h"
//using namespace std;
//
//int battleEnd(Hero* team[], int sizeOfHeroTeam, Monster* monsterTeam[], int sizeOfMonsterTeam){
//	int count = 0;
//	for(int i = 0; i < sizeOfHeroTeam; i++){
//		if(team[i]->getcurrentHealth() != 0)
//			break;
//		else
//			count++;
//		if(count == 3)
//			return -1;			
//	}
//	
//	count = 0;
//	for(int i = 0; i < sizeOfMonsterTeam; i++){
//		if(monsterTeam[i]->getHealth() != 0)
//			break;
//		else
//			count++;
//		if(count == 3)
//			return 1;
//	}
//	
//	return 0;
//}
//
//int battle(Hero* team[] , int sizeOfHeroTeam, Monster* monsterTeam[], int sizeOfMonsterTeam){
//	int sideWin;
//	do{
//		for(int i = 0; i < sizeOfHeroTeam; i++){
//			cout << "It is "<< team[i]->getName() << " turn would you like to:(1.Attack 2.Cast a spell 3.Use a potion 4.Change your armor or your weapon)" << endl;
//			int option;
//			cin >> option;
//			switch(option){
//				case 1:
//					cout << "Choose an enemy to attack ";
//					for(int j = 0; j < sizeOfMonsterTeam; j++)
//						cout << j + 1 << ")" << monsterTeam[j]->getName() << " ";
//					cout << endl;
//					{
//					bool legitOption = 0;
//					int attackOption = 0;
//					while(!legitOption){
//						cin >> attackOption;
//						if(attackOption > 0 && attackOption <= sizeOfMonsterTeam)
//							legitOption = 1;
//						else
//							cout << "Your selection must be between " << 1 << " and " << sizeOfMonsterTeam << endl;	
//					}
//					int attackPoints = team[i]->attack();
//					monsterTeam[option]->getAttacked(attackPoints);
//					break;
//					}
//				case 2:
//					cout << "Spell used" << endl;
//					break;
//				case 3:
//					cout << "Potion used" << endl;
//					break;
//				case 4:
//					cout << "Armor or weapons changed" << endl;					
//			}
//	}
//	for(int i = 0; i < sizeOfMonsterTeam; i++){
//		
//	}
//	}while((sideWin = battleEnd(team , sizeOfHeroTeam, monsterTeam, sizeOfMonsterTeam)));	
//
//	return sideWin;
//}#pragma once
#include "Living.h"
#include <string>


// Maybe some implmentations will change
// for the easiest implementaiton of battle
class heroe_squad{

private:
	int number_of_heroes;
	Hero* heroes[3];

public:
	heroe_squad(Hero* hero1, Hero* hero2=NULL, Hero* hero3=NULL, int _number_of_heroes = 1)
	:number_of_heroes(_number_of_heroes){
		heroes[0] = hero1;
		heroes[1] = hero2;
		heroes[2] = hero3;
	}
	int get_heroes_num() const{
		return number_of_heroes;
	}
    void print() const{
        for (int i=0; i < number_of_heroes; i++)
            heroes[i]->print();
    }
};



// maximum number of monsters not determined yet
class monsters_squad{
    // maximum number of monsters is not known yet, pretend is 6
private:
    int number_of_monsters;
    Monster* monsters[6];

public:
    monsters_squad(Monster* _monsters[6], int monsters_num)
	:number_of_monsters(monsters_num){
        for (int i=0; i < number_of_monsters; i++){
            monsters[i]  = _monsters[i];
        }
    }

    int get_monsters_num() const{
		return number_of_monsters;
	}
    void print() const{
        for (int i=0; i < number_of_monsters; i++)
            monsters[i]->print();
    }

};

class battle{
// battle takes place on a square on the grid(grid not made yet)
private:
    heroe_squad* heroes;
    monsters_squad* monsters;
public:
    battle(heroe_squad* heroes,  monsters_squad* monsters)
    :heroes(heroes), monsters(monsters) {
        std::cout << "A battle is about to start!" << std::endl;
    }
    // attacks will be implemented later
    // 
};


