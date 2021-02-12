#include <iostream>
#include "Living.h"
#include "battle.h"
#include "market.h"
//#include "Items_and_spells.h"
using namespace std;

int main(){
	cout << "Select number of characters in your team:(from 1 to 3)" << endl;	
	Hero* team[3];
	for(int i = 0; i < 3; i++){
		team[i] = NULL;
	}
	
	int numberOfCharacters = 10;
	while(numberOfCharacters > 3)
		cin >> numberOfCharacters;
	int option;
	for(int i = 0; i < numberOfCharacters; i++){
		cout << "Give the name of your hero: ";
		getchar();
		string name;
		getline(cin,name);
		cout << "Select the class of your hero(1.Warrior 2.Sorcerer 3.Paladin):" << endl;
		cin >> option;
		bool legalOption = 0;
		while(!legalOption)
			switch(option){
				case 1:
					team[i] = new Warrior(name);
					legalOption = 1;
					break;
				case 2:
					team[i] = new Sorcerer(name);
					legalOption = 1;
					break;
				case 3:
					team[i] = new Paladin(name);
					legalOption = 1;		
					break;
				default:
					cout << "Your number must be in range 1 to 3" << endl;	
			}
	}
	heroe_squad* team2 = new heroe_squad(team[0],team[1],team[2],numberOfCharacters);
	Dragon* drg = new Dragon("El drago", 0 , 10, 11, 1, 1, 0.1);
	Spirit* spr = new Spirit("Spirit", 2 , 10, 11, 1, 13, 0.1);
	Exosceleton* exo = new Exosceleton("Exo", 2 , 10, 12, 12, 1, 0.1);
	IceSpell* sp1 = new IceSpell(0, 10, string("Flame"), 0.4, 1.2 , 4, 1);
//	Weapon* wp1 = new Weapon(0,10,"Exalibur",12,1);
//	Armor* ar1 = new Armor(0,10,"Altyn",0.2);
	Monster* teamEnemy[3];
	teamEnemy[0] = drg;
	teamEnemy[1] = spr;
	teamEnemy[2] = exo;
	monsters_squad* team3 = new monsters_squad(teamEnemy,3);
//	Weapon* wp = new Weapon(1,2,"excalibur",11.0,1);
//	cout << team[0]->attack() << endl;
	cout << team[0]->attack(sp1) << endl;
//	team[0]->getAttacked(7);
//	drg->getAttacked(3);
	drg->getInfected(sp1);
	drg->update();
	drg->update();
	drg->update();
	drg->update();
	drg->update();
	drg->update();
	drg->update();
//	team2->buy(wp1);
//	team2->buy(ar1);
//	Battle bt = Battle(team2,team3);
//	bt.battle();
//	market* mr = new market();
//	mr->print();
	return 0;
}
