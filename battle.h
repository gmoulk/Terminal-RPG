#pragma once
#include <iostream>
#include "living.h"
#include "Items_and_spells.h"
#include <string>
#include <vector>

using namespace std;
// Maybe some implmentations will change
// for the easiest implementaiton of battle

enum{ ice,   fire,   lighting};
enum{ armor, weapon, potion  };

class heroe_squad{

private:
	int number_of_heroes;
	Hero* heroes[3];
	

    // INVENTORY
    int money;
    // ITEMS
    vector<Item*> items[3];
    vector<Spell*> spells[3];

	// added now
	Spell* useSpells(int type){
		if(this->spells[type].size() == 0){
			std::cout << "No Spells available" << endl;
			return NULL;
		}
		for(int i = 0; i < spells[type].size(); i++){
			std::cout << i + 1 << ")" << endl;
			Spell* sp = spells[type][i];
			sp->print();
			i++;
		}
		std::cout << "Choose the spell you want to use range from 1 to " << spells[type].size() << " or 0 to cancel" << endl;
		int spellOption;
		std::cin >> spellOption;
		if(spellOption > 0 && spellOption <= spells[type].size()){
			return spells[type][spellOption - 1];
		}
		return NULL;
	}


	IceSpell* useIceSpells(){  return dynamic_cast<IceSpell*>(useSpells(ice));	}
	FireSpell* useFireSpells(){	return dynamic_cast<FireSpell*>(useSpells(fire)); }
	LightingSpell* useLightSpells(){	return dynamic_cast<LightingSpell*>(useSpells(lighting)); }
	
	// inventory functions
	
	void change_armor(int hero_index, int option){
		if(items[armor].size() < option)	return;
		items[armor][option - 1] = (Armor*) heroes[hero_index - 1]->equip((Armor*)(items[armor][option - 1]));
		if(items[armor][option - 1] == NULL){
			items[armor].erase(items[armor].begin() + option - 1);
		}
	}
	
	void change_weapon(int hero_index, int option){
		if(items[weapon].size() < option)	return;
		Weapon* w1 = (Weapon*)(items[weapon].at(option - 1));
		w1->print();
		Weapon** weaps = (Weapon**) heroes[hero_index]->equip(w1);
		items[weapon][option - 1] = weaps[0];
		if(items[weapon][option - 1] == NULL)
			items[weapon].erase(items[weapon].begin() + option - 1);
		if(weaps[1] != NULL)
			items[weapon].push_back(weaps[1]);
		delete[] weaps;	
	}
	
	// attack function

	int attack(int i){
		return this->heroes[i]->attack();
	}
	 
	int attack(int i, Spell* sp){
		return this->heroes[i]->attack(sp);	
	} 
	
	void getAttacked(int attackPoints){
		for(int i = 0; i < 3; i++){
			if(!this->heroes[i]->isFaint()){
				this->heroes[i]->getAttacked(attackPoints);
				cout << " " << this->heroes[i]->getName() << endl;
				return;
			}
		}
	}


 public:

	heroe_squad(Hero* hero1, Hero* hero2=NULL, Hero* hero3=NULL, int _number_of_heroes = 1)
	:number_of_heroes(_number_of_heroes), money(200){
		heroes[0] = hero1;
		heroes[1] = hero2;
		heroes[2] = hero3;
	}
	/*
	~heroe_squad(){
		for(int i = 0; i < this->number_of_heroes; i++)
			delete this->heroes[i];
		for(int i = 0; i < this->armors.size(); i++)
			delete armors[i];
		for(int i = 0; i < this->weapons.size(); i++)
			delete weapons[i];
		for(int i = 0; i < this->potions.size(); i++)
			delete potions[i];
		for(int i = 0; i < this->fireSpells.size(); i++)
			delete fireSpells[i];
		for(int i = 0; i < this->iceSpells.size(); i++)
			delete iceSpells[i];
		for(int i = 0; i < this->lightSpells.size(); i++)
			delete lightSpells[i];						
	}	    
	*/

	int get_heroes_num() const{	return number_of_heroes; }

	// print functions
	
    void print() const{
        for (int i=0; i < number_of_heroes; i++)  heroes[i]->print();
    }


    void print_items(int type){
        for(int i = 0; i < items[type].size(); i++){
            items[type][i]->print();
        }
    }

	void printArmors()  {print_items(armor);}
	void printWeapons() {print_items(weapon);}
	void printPotions() {print_items(potion);}
	


	void print_spells(int type){
        for(int i = 0; i < spells[type].size(); i++){
            spells[type][i]->print();
        }
    }

	void printIceSpells() 		{ print_spells(ice);	 }
	void printFireSpells() 		{ print_spells(fire);	 }
	void printLightingSpells()	{ print_spells(lighting);}
	


	void checkInvetory(){
		cout << "======= ARMORS ======" << endl;
		this->printArmors();
		cout << "======= WEAPONS ======" << endl;
		this->printWeapons();
		cout << "======= Potions =======" << endl;
		this->printPotions();
		cout << "======= ICE SPELLS =======" << endl;
		this->printIceSpells();
		cout << "======= FIRE SPELLS =======" << endl;
		this->printFireSpells();
		cout << "======= LIGHTING SPELLS =======" << endl;
		this->printLightingSpells();	
	}
    
	// buy functions
	
    bool buy(Item* item, int type){
        if (item->getPrice() <= this->money){
            this->money -= item->getPrice();
			this->items[type].push_back(item);
			return 1;
        }
        return 0;
    }

    bool buy(Weapon* arm)	{	return buy(arm, weapon);	}
	bool buy(Armor* arm)	{	return buy(arm, armor);		}
	bool buy(Potion* arm)	{	return buy(arm, potion);	}
	


    bool buySpell(Spell* sp, int type){
        if(sp->getPrice() <= this->money){
			this->money -= sp->getPrice();
			this->spells[type].push_back(sp);
			return 1;
		}
    }
	
	bool buy(IceSpell* sp)		{	return buySpell(sp, ice);		 }
	bool buy(FireSpell* sp)		{	return buySpell(sp, fire);		 }
	bool buy(LightingSpell* sp)	{	return buySpell(sp, lighting);	 }

	
	// sell functions
	Item* sellItem(int i, int type){
		
		if(i <= 0 || i > this->items[type].size())
			return NULL;
		Item* toReturn = this->items[type][i - 1];
		this->items[type].erase(items[type].begin() + i - 1);
		this->money += toReturn->getPrice()/2;
		return toReturn;	
	}


	Weapon* sellWp(int i){	return dynamic_cast<Weapon*> (sellItem(i, weapon));	}
	Armor*  sellAr(int i){	return dynamic_cast<Armor*>  (sellItem(i, armor));	}
	Potion* sellPt(int i){	return dynamic_cast<Potion*> (sellItem(i, potion));	}
	


	Spell* sellSpell(int i, int type){
		if(i <= 0 || i > this->spells[type].size())
			return NULL;
		Spell* toReturn = this->spells[type][i - 1];
		this->spells[type].erase(spells[type].begin() + i - 1);
		this->money += toReturn->getPrice()/2;
		return toReturn;
	}
	

	IceSpell* sellIs(int i)			{ 	return dynamic_cast<IceSpell*> (sellSpell(i, ice));			}
	LightingSpell* sellLs(int i)	{	return dynamic_cast<LightingSpell*> (sellSpell(i, fire));	}
	FireSpell* sellFs(int i)		{	return dynamic_cast<FireSpell*> (sellSpell(i, lighting));	}
		

	void update(){
		for(int i = 0; i < 3; i++){
			if(this->heroes[i] != NULL && !this->heroes[i]->isFaint()){
				this->heroes[i]->update();
			}
		}
	}
	

	int averageLevel(){
		int avgLvl = 0;
		for(int i = 0; i < 3; i++){
			if(this->heroes[i] != NULL)
				avgLvl += this->heroes[i]->getLevel();	
		}
		avgLvl = avgLvl / 3;
		return avgLvl;
	}
	

	int getMoney(){	return money; }
	
	// NEED NAME FIX 
	void battleLost(){
		this->money = this->money / 2;
	}
	
	void battleWon(int numOfMonsters){	
			if(this->averageLevel() < 1){}
				this->money += 0.1*this->money*numOfMonsters;
			if(this->averageLevel() < 3)
				this->money += 0.2*this->money*numOfMonsters;	
			else
				this->money += 0.3*this->money*numOfMonsters;
			for(int i = 0; i < numOfMonsters; i++)
				this->heroes[i]->getExperience(numOfMonsters);
	}


	void change_armor(){
		// input
		bool want_to_change = false;    
        std::cout << "do you want to change a hero's armor?(1 = yes / 0 = no)" << std::endl;
        std::cin >> want_to_change;
		
        while(want_to_change){
			// validate if there is any armor
			cout << "Would you like to take out your armor?(1 = Yes/ 0 = No)" << endl;
			bool takeOut;
			cin >> takeOut;
			if(takeOut){
				std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
				int hero_index;
				cin >> hero_index;
				Armor* arm = this->heroes[hero_index - 1]->takeOutArmor();
				if(arm != NULL)
					this->items[armor].push_back(arm);
			}
			if (items[armor].size() == 0){
				std::cout << "You have no armor in your inventory" << std::endl;
				return;
			}
			// input
		    int hero_index;
            std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
            std::cin >> hero_index;
            std::cout << "Select the armor you want to equip: " << endl;
            std::cout << "ARMOR LIST:\n--------------------"<<std::endl;
			// print armor list
			for(int i = 0; i < this->items[armor].size(); i++){
              	Armor* arm = (Armor*)(this->items[armor].at(i));
               	cout << i + 1 << ")";
				arm->print();
			}
			std::cout << "             \n--------------------"<<std::endl;
			// input
			int option;
			cin >> option;
			this->change_armor(hero_index, option);
			cout << "Would you want to change something else?" << endl;
			cin >> want_to_change;
        }
	}


	void change_weapon(){

		bool want_to_change;
		std::cout << "Do you want to change a hero's weapon?(1 = yes / 0 = no)" << std::endl;
        std::cin >> want_to_change;
	
	    while(want_to_change){
	    	cout << "Would you like to take out your weapons?(1 = Yes/ 0 = No)" << endl;
			bool takeOut;
			cin >> takeOut;
			if(takeOut){
				std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
				int hero_index;
				cin >> hero_index;
				Weapon** wps = this->heroes[hero_index - 1]->takeOutWeapons();
				if(wps[0] != NULL)
					this->items[weapon].push_back(wps[0]);
				if(wps[1] != NULL)
					this->items[weapon].push_back(wps[1]);
				delete[] wps;	
			}
			if (items[weapon].size() == 0){
				std::cout << "You have no weapon in your inventory" << std::endl;
				return;
			}
			//input
            int hero_index;
            std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
            std::cin >> hero_index;
            std::cout << "Select the weapon you want to equip: " << endl;
			// print weapons
			std::cout << "WEAPONS LIST:\n--------------------"<<std::endl;
            for(int i = 0; i < this->items[weapon].size(); i++){
               	Weapon* wep = (Weapon*)(this->items[weapon].at(i));
               	cout << i + 1 << ")";
				wep->print();
			}
			std::cout << "             \n--------------------"<<std::endl;
			// input
			int option;
			cin >> option;
			this->change_weapon(hero_index-1, option);
			cout << "Would you want to change something else?" << endl;
            cin >> want_to_change;
        }
	}

	void usePotion(int hero_index){
		this->printPotions();
		cout << "Select one of the above potions range 1 to " << this->items[2].size() << " or type 0 to cancel." << endl;
		int option;
		cin >> option;
		if(option > 0 && option <= this->items[2].size() && this->heroes[hero_index - 1]->use_potion((Potion*) this->items[2].at(option - 1)) )
			items[2].erase(items[2].begin() + option - 1);
	}
	
    friend class Battle;
};



// maximum number of monsters not determined yet
class monsters_squad{
    // maximum number of monsters is not known yet, pretend is 6
private:
    int number_of_monsters;
    Monster* monsters[6];
	 
    void getAttacked(int num,int attack){
    	this->monsters[num]->getAttacked(attack);
	}
	

	void getInfected(int index,Spell* sp){
		// check type
		if (dynamic_cast<FireSpell*>(sp)){
			this->monsters[index]->getInfected((FireSpell *)sp);
		}else if (dynamic_cast<IceSpell*>(sp)){
			this->monsters[index]->getInfected((IceSpell *)sp);
		}else{
			this->monsters[index]->getInfected((LightingSpell *)sp);
		}
	}
	
	
	void update(){
		for(int i = 0; i < 6; i++){
			if(this->monsters[i] != NULL && !this->monsters[i]->isFaint()){
				this->monsters[i]->update();
			}
		}
	}

public:
    monsters_squad(Monster* _monsters[6], int monsters_num)
	:number_of_monsters(monsters_num){
		for(int i = 0; i < 6; i++)
			monsters[i] = NULL;
        for (int i=0; i < number_of_monsters; i++)
            monsters[i]  = _monsters[i];
    }

    int get_monsters_num() const{
		return number_of_monsters;
	}
	
    void print() const{
        for (int i=0; i < number_of_monsters; i++)
            monsters[i]->print();
    }
   
	~monsters_squad(){
		for(int i = 0; i < this->number_of_monsters; i++)
			delete monsters[i];
	}
    friend class Battle;
};



class Battle{
// battle takes place on a square on the grid(grid not made yet)
private:
    heroe_squad* heroes;
    monsters_squad* monsters;
    bool heroes_are_dead(){
        for(int i = 0; i < heroes->get_heroes_num(); i++){
            if (heroes->heroes[i]->getcurrentHealth() > 0){
                return false;
            }
        }
        return true;
    }
    
	bool monsters_are_dead(){
        for(int i = 0; i < monsters->get_monsters_num(); i++){
            if (monsters->monsters[i]->getcurrentHealth() > 0){
                return false;
            }
        }
        return true;
    }

	void heroes_take_action(){
		int monster_index, action;
		// input
		cout << "===== HERO TURN ====" << endl;
		for(int i = 0; i < this->heroes->number_of_heroes; i++){
			cout << this->heroes->heroes[i]->getName() << " turn" << endl;
        	cout << "What would you want to do?1)Normal attack 2)Spell Attack 3)Consume potion)" << endl;
        	cin >> action;

       		if(action == 1){
				// option 1: attack with weapon
           		int attack = this->heroes->attack(i);
				cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << endl;
				int monster_index;
				cin >> monster_index;
				this->monsters->getAttacked(monster_index - 1, attack);
			
			}else if(action == 2){	
				// option 2: attack with spell
				cout << "Select the type of spell you want to use (1)Ice Spell (2)Fire Spell (3)Lighting Spell" << endl;
				int spellType = 4;
				while(spellType > 3 || spellType < 0){
					cin >> spellType ;
					cout << "What spell would you like to use?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
				}
				Spell* sp;
				if(spellType == 1){
					sp = this->heroes->useIceSpells();
				}else if(spellType == 2){
					sp = this->heroes->useFireSpells();
				}else{
					sp = this->heroes->useLightSpells();
				}
				if(sp != NULL){
						cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << ")" << endl;
						int monster_index;
						cin >> monster_index;
						this->monsters->getAttacked(monster_index - 1, heroes->attack(i,sp));
						this->monsters->getInfected(monster_index - 1, sp);
				}
			}
			else if(action == 3 && heroes->items[potion].size() != 0){
				this->heroes->printPotions();
				cout << "Select one of the above potions range 1 to " << this->heroes->items[potion].size() << " or type 0 to cancel." << endl;
				int option;
				cin >> option;
				if(	option > 0 && option <= this->heroes->items[potion].size() 
					&& this->heroes->heroes[i]->use_potion((Potion*)(heroes->items[potion][option - 1])))
					heroes->items[potion].erase(heroes->items[potion].begin() + option - 1);
			}
		}
	}


public:

    Battle(heroe_squad* heroes,  monsters_squad* monsters)
    :heroes(heroes), monsters(monsters) {
        std::cout << "A battle is about to start!" << std::endl;
    }
	
	void displayStats() const{
		cout << "======== HEROES =============" << endl;
		for(int i = 0; i < this->heroes->number_of_heroes; i++)
			if(!this->heroes->heroes[i]->isFaint())
				this->heroes->heroes[i]->print();	
		cout << "======== MONSTERS =============" << endl;
		for(int i = 0; i < this->monsters->number_of_monsters; i++)
			if(!this->monsters->monsters[i]->isFaint())
				this->monsters->monsters[i]->print();
	}
	

    // actual battle
    bool battle(){  // the main function of the battle, everyhting happens in here
        //battle loop
        for(int round = 1; (!heroes_are_dead() && !monsters_are_dead()); round++){
			std::cout << "ROUND: " << round << std::endl;
			cout << "Would you like to print the stats of the battle participants?(1 = Yes/ 0 = No)" << endl;
			bool printStats;
			cin >> printStats;
			if(printStats){
				this->displayStats();
			}	
			heroes->change_armor();
			heroes->change_weapon();
			heroes_take_action();	// attack with spell, attack with weapon, use potion

            // pc's turn
            for (int i = 0; i < monsters->get_monsters_num(); i++){
                if (monsters->monsters[i]->getcurrentHealth() != 0){
                    this->heroes->getAttacked(monsters->monsters[i]->attack());
                }
            }
			this->heroes->update();
			this->monsters->update();
        }
        for(int i = 0; i < heroes->get_heroes_num(); i++)
        	heroes->heroes[i]->revive();
        // end of battle
        return monsters_are_dead(); 
    }
    
    ~Battle(){
    	delete this->monsters;
	}
};
