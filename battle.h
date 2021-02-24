#pragma once
#include "living.h"
#include "Items_and_spells.h"
#include <string>
#include <vector>


// Maybe some implmentations will change
// for the easiest implementaiton of battle
class heroe_squad{

private:
	int number_of_heroes;
	Hero* heroes[3];
	int money;
	vector<Armor*> armors;
	vector<Weapon*> weapons;
	vector<IceSpell*> iceSpells;
	vector<FireSpell*> fireSpells;
	vector<LightingSpell*> lightSpells;
	vector<Potion*> potions;


	
	IceSpell* useIceSpells(){
		if(this->iceSpells.size() == 0){
			cout << "No Ice Spells available" << endl;
			return NULL;
		}
		for(int i = 0; i < iceSpells.size(); i++){
			cout << i + 1 << ")" << endl;
			Spell* sp = iceSpells[i];
			sp->print();
			i++;
		}
		cout << "Choose the spell you want to use range from 1 to " << iceSpells.size() << " or 0 to cancel" << endl;
		int spellOption;
		cin >> spellOption;
		if(spellOption > 0 && spellOption <= iceSpells.size()){
			return iceSpells[spellOption - 1];
		}
		return NULL;		
	}
	
	FireSpell* useFireSpells(){
		if(this->fireSpells.size() == 0){
			cout << "No Fire Spells available" << endl;
			return NULL;
		}
		for(int i = 0; i < fireSpells.size(); i++){
			cout << i + 1 << ")" << endl;
			Spell* sp = fireSpells[i];
			sp->print();
			i++;
		}
		cout << "Choose the spell you want to use range from 1 to " << iceSpells.size() << " or 0 to cancel" << endl;
		int spellOption;
		cin >> spellOption;
		if(spellOption > 0 && spellOption <= fireSpells.size()){
			return fireSpells[spellOption - 1];
		}
		return NULL;		
	}
	
	LightingSpell* useLightSpells(){
		if(this->lightSpells.size() == 0){
			cout << "No Lighting Spells available" << endl;
			return NULL;
		}
		for(int i = 0; i < lightSpells.size(); i++){
			cout << i + 1 << ")" << endl;
			Spell* sp = lightSpells[i];
			sp->print();
			i++;
		}
		cout << "Choose the spell you want to use range from 1 to " << lightSpells.size() << " or 0 to cancel" << endl;
		int spellOption;
		cin >> spellOption;
		if(spellOption > 0 && spellOption <= lightSpells.size()){
			return lightSpells[spellOption - 1];
		}
		return NULL;		
	}

	// inventory functions
	
	
	void change_armor(int hero_index, int option){
		if(armors.size() < option)
			return;
		armors[option - 1] = (Armor*) heroes[hero_index - 1]->equip(armors[option - 1]);
		if(armors[option - 1] == NULL){
			armors.erase(armors.begin() + option - 1);
		}
		for(int i = 0; i < armors.size(); i++){
		if(armors[i] == NULL && (i != 19 || armors[i + 1] != NULL)){
			Armor* temp = armors[i];
			armors[i] = armors[i + 1];
			armors[i + 1] = temp;
			}
		}
	}
	
	void change_weapon(int hero_index, int option){
		if(weapons.size() < option)
			return;
		Weapon* w1 = weapons.at(option - 1);
		w1->print();
		Weapon** weaps = (Weapon**) heroes[hero_index]->equip(w1);
		weapons[option - 1] = weaps[0];
		if(weapons[option - 1] == NULL)
			weapons.erase(weapons.begin() + option - 1); 
		for(int i = 0; i < weapons.size(); i++){
		if(armors[i] == NULL && (i != 19 || armors[i + 1] != NULL)){
			Weapon* temp = weapons[i];
			weapons[i] = weapons[i + 1];
			weapons[i + 1] = temp;
			}
		}
		if(weaps[1] != NULL)
			weapons.push_back(weaps[1]);
		delete[] weaps;	
	}
	
	
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


	int get_heroes_num() const{
		return number_of_heroes;
	}

	
	// print functions
	
    void print() const{
        for (int i=0; i < number_of_heroes; i++)
            heroes[i]->print();
    }


	void printArmors(){
		for(int i = 0; i < armors.size(); i++){
			Armor* ar = this->armors[i];
			ar->print();
		}
	}
	
	void printWeapons(){
		for(int i = 0; i < weapons.size(); i++){
			Weapon* wp = this->weapons[i];
			wp->print();
		}
	}
	
	void printPotions(){
		for(int i = 0; i < potions.size(); i++){
			Potion* pt = this->potions[i];
			pt->print();
		}
	}
	
	void printIceSpells(){
		for(int i  = 0; i < iceSpells.size(); i++){
			IceSpell* is = this->iceSpells[i];
			is->print();
		}
	}
	
	void printFireSpells(){
		for(int i  = 0; i < fireSpells.size(); i++){
			FireSpell* fs = this->fireSpells[i];
			fs->print();
		}
	}
	
	void printLightingSpells(){
		for(int i  = 0; i < lightSpells.size(); i++){
			LightingSpell* ls = this->lightSpells[i];
			ls->print();
		}
	}
	

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
	
	bool buy(Weapon* wep){
		if(wep->getPrice() <= this->money){
			this->money -= wep->getPrice();
			this->weapons.push_back(wep);
			cout << "Weapon " << wep->getName() << " bought!" << endl;
			return 1;
		}
		return 0;
	}
	
	bool buy(Armor* arm){
		if(arm->getPrice() <= this->money){
			this->money -= arm->getPrice();
			this->armors.push_back(arm);
			return 1;
		}
		return 0;	
	}
	
	bool buy(IceSpell* sp){
		if(sp->getPrice() <= this->money){
			this->money -= sp->getPrice();
			this->iceSpells.push_back(sp);
			return 1;
		}
		return 0;
	}
	
	bool buy(FireSpell* sp){
		if(sp->getPrice() <= this->money){
			this->money -= sp->getPrice();
			this->fireSpells.push_back(sp);
			return 1;
		}
		return 0;
	}
	
	bool buy(LightingSpell* sp){
		if(sp->getPrice() <= this->money){
			this->money -= sp->getPrice();
			this->lightSpells.push_back(sp);
			return 1;
		}
		return 0;
	}
	
	bool buy(Potion* pt){
		if(pt->getPrice() <= this->money){
			this->money -= pt->getPrice();
			this->potions.push_back(pt);
			return 1;
		}
		return 0;
	}
	
	// sell functions

	Weapon* sellWp(int i){
		if(i <= 0 || i > this->weapons.size())
			return NULL;
		Weapon* wpToReturn = this->weapons[i - 1];
		this->weapons.erase(weapons.begin() + i - 1);
		this->money += wpToReturn->getPrice()/2;
		return wpToReturn;	
	}
	
	Armor* sellAr(int i){
		if(i <= 0 || i > this->armors.size())
			return NULL;
		Armor* arToReturn = this->armors[i - 1];
		this->armors.erase(armors.begin() + i - 1);
		this->money += arToReturn->getPrice()/2;
		return arToReturn;		
	}
	
	Potion* sellPt(int i){
		if(i <= 0 || i > this->potions.size())
			return NULL;
		Potion* ptToReturn = this->potions[i - 1];
		this->potions.erase(potions.begin() + i - 1);
		this->money += ptToReturn->getPrice()/2;
		return ptToReturn;		
	}
	
	IceSpell* sellIs(int i){
		if(i <= 0 || i > this->iceSpells.size())
			return NULL;
		IceSpell* isToReturn = this->iceSpells[i - 1];
		this->iceSpells.erase(iceSpells.begin() + i - 1);
		this->money += isToReturn->getPrice()/2;
		return isToReturn;		
	}
	
	LightingSpell* sellLs(int i){
		if(i <= 0 || i > this->lightSpells.size())
			return NULL;
		LightingSpell* lsToReturn = this->lightSpells[i - 1];
		this->lightSpells.erase(lightSpells.begin() + i - 1);
		this->money += lsToReturn->getPrice()/2;
		return lsToReturn;		
	}
	
	FireSpell* sellFs(int i){
		if(i <= 0 || i > this->fireSpells.size())
			return NULL;
		FireSpell* fsToReturn = this->fireSpells[i - 1];
		this->fireSpells.erase(fireSpells.begin() + i - 1);
		this->money += fsToReturn->getPrice()/2;
		return fsToReturn;		
	}		
	
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
	
	int getMoney(){
		return money;
	}
	
	// NEED NAME FIX 
	void battleLost(){
		this->money = this->money / 2;
	}
	
	void battleWon(int numOfMonsters){	
			if(this->averageLevel() < 1)
				this->money += 0.1*this->money*numOfMonsters;
			if(this->averageLevel() < 3)
				this->money += 0.2*this->money*numOfMonsters;	
			else
				this->money += 0.3*this->money*numOfMonsters;
			for(int i = 0; i < number_of_heroes; i++)
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
					this->armors.push_back(arm);
			}
			if (armors.size() == 0){
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
			for(int i = 0; i < this->armors.size(); i++){
              	Armor* arm = this->armors.at(i);
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
					this->weapons.push_back(wps[0]);
				if(wps[1] != NULL)
					this->weapons.push_back(wps[1]);
				delete[] wps;	
			}
			if (weapons.size() == 0){
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
            for(int i = 0; i < this->weapons.size(); i++){
               	Weapon* wep = this->weapons.at(i);
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
		cout << "Select one of the above potions range 1 to " << this->potions.size() << " or type 0 to cancel." << endl;
		int option;
		cin >> option;
		if(option > 0 && option <= this->potions.size() && this->heroes[hero_index - 1]->use_potion(this->potions[option - 1]) )
			potions.erase(potions.begin() + option - 1);
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
				if(spellType == 1)
					sp = this->heroes->useIceSpells();
				else if(spellType == 2)
					sp = this->heroes->useFireSpells();	
				else
					sp = this->heroes->useLightSpells();
				if(sp != NULL){
					cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << ")" << endl;
					int monster_index;
					cin >> monster_index;
					this->monsters->getAttacked(monster_index - 1, heroes->attack(i,sp));
					this->monsters->getInfected(monster_index - 1, sp);
				}	
			}
			else if(action == 3 && heroes->potions.size() != 0){
				this->heroes->usePotion(i);
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
                if (!monsters->monsters[i]->isFaint()){
                    this->heroes->getAttacked(monsters->monsters[i]->attack());
                }
            }
			this->heroes->update();
			this->monsters->update();
        }
        for(int i = 0; i < heroes->get_heroes_num(); i++){
			if(heroes->heroes[i] != NULL)
				heroes->heroes[i]->revive();
		}
        // end of battle
		bool win = monsters_are_dead();
		if(win)
			cout << "Battle Won!" << endl;
		else 
			cout << "Battle Lost!" << endl;
        return monsters_are_dead(); 
    }
    
    ~Battle(){
    	delete this->monsters;
	}
};
