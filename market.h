#pragma once
#include "Items_and_spells.h"
#include "battle.h"

using namespace std;

class market{
	private:
		vector<Armor*> armors;
		vector<Weapon*> weapons;
		vector<IceSpell*> iceSpells;
		vector<FireSpell*> fireSpells;
		vector<LightingSpell*> lightSpells;
		vector<Potion*> potions;
		heroe_squad* hs;
	public:
		market(heroe_squad* hs);
		
		void print();
		
		void printWeapons();
		
		void printArmor();
		
		void printSpells();
		
		void printPotion();
		
		void interact();
		
		~market();
};
