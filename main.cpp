#include <iostream>
#include "Living.h"
//#include "Items_and_spells.h"
using namespace std;

int main(){
	cout << "Select number of characters in your team:(from 1 to 3)" << endl;	
	Hero* team[3];
	for(int i = 0; i < 3; i++){
		team[i] = NULL;
	}
	
	int numberOfCharacters;
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
	Dragon* drg = new Dragon("El drago", 2 , 10, 11, 12, 13, 0.1);
	Spirit* spr = new Spirit("Spirit", 2 , 10, 11, 12, 13, 0.1);
	Exosceleton* exo = new Exosceleton("Exo", 2 , 10, 11, 12, 13, 0.1);
	
	Weapon* wp = new Weapon(1,2,"excalibur",11.0,1);
	return 0;
}
