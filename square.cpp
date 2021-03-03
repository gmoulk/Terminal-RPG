#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "market.h"
#include "square.h"
#include <cstring>

monsters_squad* commonSquare::create_monsters_for_battle(heroe_squad* hs, int numberOfMonsters){
	int maxNumOfMonsters = 12;
	ifstream in("enemies.txt");	
	this->averageLevel = hs->averageLevel();
	cout << "Ambush!Monsters attack us!" << endl;
	Monster* mteam[numberOfMonsters];
	char str[255];
	// FOR EVERY MONSTER
	for(int i = 0; i < numberOfMonsters - 1; i++){
		// DETERMINE LEVEL OF MONSTER
		int levelOfMonster = hs->averageLevel();
		int typeOfMonster = 0;
		in.clear();
		in.seekg(0);
		int num = rand() % maxNumOfMonsters;	
		cout << "NUM " << num << " MAXNUM " << maxNumOfMonsters << endl;
		for (int k = 0 ; k < num*8; k++){ 
    		in.ignore(255,'\n');
    	}
    	int j = 1;
		string name;
		int hp, attackMax, attackMin, deffence;
		double probOfDogde;				
		while(in) {		 
    	    in.getline(str, 255);  // delim defaults to '\n'
    		char* token1 = strtok(str,":");				
			do{   	
				if(j % 2==0){
					if(j == 2){
						cout << "DEBUG " << string(token1) << endl;
						if(token1[0] == 'D')
							typeOfMonster = 0;
						else if(token1[1] == 'S')
							typeOfMonster = 1;
						else
							typeOfMonster = 2;
					}		
					if(j == 4)
					    name = string(token1);
					else if(j == 6)
					    hp = atoi(token1);
					else if(j == 8)
					    attackMax = atoi(token1);	
					else if(j == 10)
						attackMin = atoi(token1);			
					else if(j == 12)
						deffence = atoi(token1);
					else if(j == 14)
						probOfDogde = atof(token1)*100;				
				}
				j++;
			    token1 = strtok(NULL,"\n");
			}while(token1 != NULL);					
  		}
		if(typeOfMonster == 0){
			mteam[i] = new Dragon(name,levelOfMonster,hp,attackMax,attackMin,deffence,probOfDogde);   	
		}else if(typeOfMonster == 1){
			mteam[i] = new Spirit(name,levelOfMonster,hp,attackMax,attackMin,deffence,probOfDogde);						
		}else{
			mteam[i] = new Exosceleton(name,levelOfMonster,hp,attackMax,attackMin,deffence,probOfDogde);						
		}
	}
			// close file
	in.close();	
	monsters_squad* ms = new monsters_squad(mteam,numberOfMonsters - 1);
	return ms;
}

commonSquare::commonSquare(heroe_squad* hs, bool let_battle_happen ){
			
	if(let_battle_happen){ // BATTLE WILL HAPPEN
		battleOpen = true;
		this->number_of_monsters = rand() % 7 + 1;	
		monsters_squad* ms = create_monsters_for_battle(hs, number_of_monsters);
		// BATTLE STARTS HERE
		this->bt = new Battle(hs,ms);
	}else{
		// BATTLE WIL NOT HAPPEN
		battleOpen = false;	
	}
	this->hs = hs;	 
}
		
void commonSquare::interact(){
	bool win = bt->battle();
    (win)?this->hs->battleWon(number_of_monsters):this->hs->battleLost();				
}
		
commonSquare::~commonSquare(){
	if(this->isBattleOpen())
		delete bt;
}
		
bool commonSquare::isBattleOpen(){
	return this->battleOpen;
}