#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "market.h"
#include <cstring>

class square{
	public:
		square(){}
		
		virtual void interact() = 0;
		virtual ~square(){};	
};

class marketSquare: public square{
	private:
		market* mrk;
	public:
		marketSquare(heroe_squad* hs){
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
		Battle* bt;
		heroe_squad* hs;
		int number_of_monsters;
		monsters_squad* create_monsters_for_battle(heroe_squad* hs, int numberOfMonsters);
	public: 
		commonSquare(heroe_squad* hs, bool let_battle_happen );
		
		void interact();
		
		~commonSquare();
		
		bool isBattleOpen();	
};
