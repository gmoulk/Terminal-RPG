#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "market.h"
class grid{
	protected:
		bool walkable;
};

class marketSquare: public grid{
	private:
		market mrk;
};

class commonSquare: public grid{
	int averageLevel;
	double persentageOfBattle;
	bool battleOpen;
	public: 
		commonSquare(heroe_squad* hs){
			srand((unsigned) time(NULL));
			this->persentageOfBattle = (double)rand() / RAND_MAX;
			double currentPersentage = (double)rand() / RAND_MAX;
			if(currentPersentage >= this->persentageOfBattle){
				battleOpen = true;
				ifstream in("weapons.txt");	
				this->averageLevel = hs->averageLevel();
				cout << "Ambush!Monsters attack us!" << endl;
				int numberOfMonsters = rand() % 7 + 1;
				Monster* mteam[numberOfMonsters];
				char str[255];
				for(int i = 0; i < numberOfMonsters; i++){
					int levelOfMonster = rand() % (this->averageLevel + 3);
					int typeOfMonster = rand() % 3;
					if(typeOfMonster == 0){
						int num = 4;
						//int num = rand() % 5;
						for (int i = 0 ; i < num*8; i++){ 
    						in.ignore(255,'\n');
    					}
    					int j = 1;
						string name;
						int hp;
						int attackMax;
						int attackMin;
						int deffence;
						double probOfDogde;				
						while(in) {		 
    						in.getline(str, 255);  // delim defaults to '\n'
    						char* token1 = strtok(str,":");				
							do{   	
								if(j % 2==0){
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
									probOfDogde = atof(token1);				
								}
								j++;
								token1 = strtok(NULL,"\n");
							}while(token1 != NULL);					
  						}
						mteam[i] = new Dragon(name,levelOfMonster,hp,attackMax,attackMin,deffence,probOfDogde);   	
					}
					else if(typeOfMonster == 1){
						int num = 4;
						//int num = rand() % 5;
						for (int i = 0 ; i < num*8 + 8*4; i++){ 
    						in.ignore(255,'\n');
    					}
    					int j = 1;
						string name;
						int hp;
						int attackMax;
						int attackMin;
						int deffence;
						double probOfDogde;
						while(in) {		 
    						in.getline(str, 255);  // delim defaults to '\n'
    						char* token1 = strtok(str,":");				
							do{   	
								if(j % 2==0){
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
									probOfDogde = atof(token1);				
								}
								j++;
								token1 = strtok(NULL,"\n");
							}while(token1 != NULL);					
  						}
						mteam[i] = new Spirit(name,levelOfMonster,hp,attackMax,attackMin,deffence,probOfDogde);						
					}
					else{
						int num = 4;
						//int num = rand() % 5;
						for (int i = 0 ; i < num*8 + 8*8; i++){ 
    						in.ignore(255,'\n');
    					}
    					int j = 1;
						string name;
						int hp;
						int attackMax;
						int attackMin;
						int deffence;
						double probOfDogde;
						while(in) {		 
    						in.getline(str, 255);  // delim defaults to '\n'
    						char* token1 = strtok(str,":");				
							do{   	
								if(j % 2==0){
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
									probOfDogde = atof(token1);				
								}
								j++;
								token1 = strtok(NULL,"\n");
							}while(token1 != NULL);					
  						}
						mteam[i] = new Exosceleton(name,levelOfMonster,hp,attackMax,attackMin,deffence,probOfDogde);						
					}
				}
				monsters_squad* ms = new monsters_squad(mteam,numberOfMonsters);
				Battle(hs,ms);
			}
			else
				battleOpen = false;	 
			
		}
		
};


