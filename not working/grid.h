#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "market.h"



class grid{
	protected:
		bool walkable;
	public:
		grid(bool walkable) : walkable(walkable){}
		
		bool isWalkable(){
			return walkable;
		}	
};

class nonAccessible : public grid{
	public :
		nonAccessible() : grid(walkable) {}
};


class marketSquare: public grid{
	private:
		market* mrk;
	public:
		marketSquare(heroe_squad* hs) : grid(true){
			mrk = new market(hs);
			mrk->interact();
		}
		void interact(){
			this->mrk->interact();
		}	
};


class commonSquare: public grid{
	int averageLevel;
	double persentageOfBattle;
	bool battleOpen;
	public: 
		commonSquare(heroe_squad* hs, bool let_battle_happen = true) : grid(true){
			srand((unsigned) time(NULL));
			this->persentageOfBattle = (double)rand() / RAND_MAX;
			double currentPersentage = (double)rand() / RAND_MAX;

			if((currentPersentage >= (this->persentageOfBattle)) && let_battle_happen){ // BATTLE WILL HAPPEN
				battleOpen = true;
				ifstream in("enemies.txt");	
				this->averageLevel = hs->averageLevel();
				cout << "Ambush!Monsters attack us!" << endl;
				// NUMBER OF MONSTERS HERE
				int numberOfMonsters = 2;	
				Monster* mteam[numberOfMonsters];
				char str[255];
				// FOR EVERY MONSTER
				for(int i = 0; i < numberOfMonsters; i++){
					// DETERMINE LEVEL OF MONSTER
					int levelOfMonster = 0;
					cout << "LEVEL " << levelOfMonster << endl;
					int typeOfMonster = 0;
					in.clear();
					in.seekg(0);
					//
					int num = rand() % 4;	// 4 different names for each monster
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
									cout << "NAME " << name << " " << j << endl;
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
								probOfDogde = atof(token1);				
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

				monsters_squad* ms = new monsters_squad(mteam,numberOfMonsters);

				// BATTLE STARTS HERE
				Battle* bt = new Battle(hs,ms);
				bool win = bt->battle();
				if(win){
					hs->battleWon(numberOfMonsters);	
				}
				else{
					hs->battleLost();
				}
				delete ms;	

			}else  // BATTLE WIL NOT HAPPEN
				battleOpen = false;	 
		}
		
};
