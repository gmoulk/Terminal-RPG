#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "market.h"
#include <cstring>

class square{
	protected:
		bool walkable;
	public:
		square(bool walkable) : walkable(walkable){}
		
		bool isWalkable(){
			return walkable;
		}	
};

class nonAccessible : public square{
	public :
		nonAccessible() : square(walkable) {}
};


class marketSquare: public square{
	private:
		market* mrk;
	public:
		marketSquare(heroe_squad* hs) : square(true){
			mrk = new market(hs);
			mrk->interact();
		}
		void interact(){
			this->mrk->interact();
		}
		~marketSquare(){
			delete mrk;
		}	
};


class commonSquare: public square{
	private:
		int averageLevel;
		double persentageOfBattle;
		bool battleOpen;
		monsters_squad* create_monsters_for_battle(heroe_squad* hs, int numberOfMonsters){
			ifstream in("enemies.txt");	
			this->averageLevel = hs->averageHeroLevel();
			cout << "Ambush!Monsters attack us!" << endl;
			Monster* mteam[numberOfMonsters];
			char str[255];
			// FOR EVERY MONSTER
			for(int i = 0; i < numberOfMonsters; i++){
				// DETERMINE LEVEL OF MONSTER
				int levelOfMonster = 0;	// FIX THIS
				cout << "LEVEL " << levelOfMonster << endl;
				int typeOfMonster = 0;
				in.clear();
				in.seekg(0);
				// 4 different names for each monster
				int num = rand() % 4;	
				for (int i = 0 ; i < num*8; i++){ 
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
							if(j == 4){
									name = string(token1);
								}
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
			monsters_squad* ms = new monsters_squad(mteam,numberOfMonsters);
			return ms;
		}
	public: 
		commonSquare(heroe_squad* hs, bool let_battle_happen ) : square(true){
			
			if(let_battle_happen){ // BATTLE WILL HAPPEN
				battleOpen = true;
				int numberOfMonsters = 1;	
				monsters_squad* ms = create_monsters_for_battle(hs, numberOfMonsters);
				// BATTLE STARTS HERE
				Battle* bt = new Battle(hs,ms);
				bool win = bt->battle();
				(win)?hs->battleWon(numberOfMonsters):hs->battleLost();
				delete bt;
				
			}else{
				// BATTLE WIL NOT HAPPEN
				battleOpen = false;	
			}
				 
		}
		
};