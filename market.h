#pragma once
#include "Items_and_spells.h"
#include "battle.h"

using namespace std;


class market{
	private:
		vector<Item*> items[3];
	    vector<Spell*> spells[3];
				
		heroe_squad* hs;
		void buy_spell();
		void buy_spell(int type);
		void buy_item(int type);
		void buy_item();
		void buy();
		void sell();
		

	public:
		market(heroe_squad* hs);
		
		void print();

		void printSpell(int type);
		
		void printItems(int type);

		void printWeapons();
		
		void printArmors();
		
		void printSpells();
		
		void printPotions();

		void sellItem(int type);
		
		void sellSpell(int type);
		
		void interact();	
		
		~market();
};