#pragma once
#include "Living.h"
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
	vector<Spell*> spells;
public:
	heroe_squad(Hero* hero1, Hero* hero2=NULL, Hero* hero3=NULL, int _number_of_heroes = 1)
	:number_of_heroes(_number_of_heroes), money(200){
		heroes[0] = hero1;
		heroes[1] = hero2;
		heroes[2] = hero3;
	}
	
	int get_heroes_num() const{
		return number_of_heroes;
	}
	
    void print() const{
        for (int i=0; i < number_of_heroes; i++)
            heroes[i]->print();
    }

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
				return;
			}
		}
	}
	
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
	
	bool buy(Spell* sp){
		if(sp->getPrice() <= this->money){
			this->money -= sp->getPrice();
			this->spells.push_back(sp);
			return 1;
		}
		return 0;
	}	    
    friend class Battle;
};



// maximum number of monsters not determined yet
class monsters_squad{
    // maximum number of monsters is not known yet, pretend is 6
private:
    int number_of_monsters;
    Monster* monsters[6];
public:
    monsters_squad(Monster* _monsters[6], int monsters_num)
	:number_of_monsters(monsters_num){
        for (int i=0; i < number_of_monsters; i++){
            monsters[i]  = _monsters[i];
        }
    }

    int get_monsters_num() const{
		return number_of_monsters;
	}
    void print() const{
        for (int i=0; i < number_of_monsters; i++)
            monsters[i]->print();
    }
    
    void getAttacked(int num,int attack){
    	this->monsters[num]->getAttacked(attack);
	}
	
	void getAttacked(int num,FireSpell* sp){
		this->monsters[num]->getInfected(sp);
	}
	
	void getAttacked(int num,IceSpell* sp){
		this->monsters[num]->getInfected(sp);
	}
	
	void getAttacked(int num,LightingSpell* sp){
		this->monsters[num]->getInfected(sp);
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
            if (heroes->heroes[i]->getcurrentHealth() != 0){
            	heroes->heroes[i]->print();
                return false;
            }
        }
        return true;
    }
    
	bool monsters_are_dead(){
        for(int i = 0; i < monsters->get_monsters_num(); i++){
            if (monsters->monsters[i]->getHealth() != 0){
                return false;
            }
        }
        return true;
    }

	void heroes_change_armor(){
		// input
		bool want_to_change = false;    
        std::cout << "do you want to change a hero's armor?(1 = yes / 0 = no)" << std::endl;
        std::cin >> want_to_change;
		
        while(want_to_change){
			// input
		    int hero_index;
            std::cout << "Pick a hero(" << 1 << "-" << heroes->get_heroes_num() << ")" << std::endl;
            std::cin >> hero_index;
            std::cout << "Select the armor you want to equip: " << endl;
            std::cout << "ARMOR LIST:\n--------------------"<<std::endl;
			// print armor list
			for(int i = 0; i < heroes->armors.size(); i++){
              	Armor* arm = heroes->armors.at(i);
               	cout << i + 1 << ")";
				arm->print();
			}
			std::cout << "             \n--------------------"<<std::endl;
			// input
			int option;
			cin >> option;
			heroes->change_armor(hero_index, option);
			cout << "Would you want to change something else?" << endl;
			cin >> want_to_change;
        }
	}


	void heroes_change_weapon(){

		bool want_to_change;
		std::cout << "Do you want to change a hero's weapon?(1 = yes / 0 = no)" << std::endl;
        std::cin >> want_to_change;
      
	    while(want_to_change){
			//input
            int hero_index;
            std::cout << "Pick a hero(" << 1 << "-" << heroes->get_heroes_num() << ")" << std::endl;
            std::cin >> hero_index;
            std::cout << "Select the weapon you want to equip: " << endl;
			// print weapons
			std::cout << "WEAPONS LIST:\n--------------------"<<std::endl;
            for(int i = 0; i < heroes->weapons.size(); i++){
               	Weapon* wep = heroes->weapons.at(i);
               	cout << i + 1 << ")";
				wep->print();
			}
			std::cout << "             \n--------------------"<<std::endl;
			// input
			int option;
			cin >> option;
			heroes->change_weapon(hero_index-1, option);
			cout << "Would you want to change something else?" << endl;
            cin >> want_to_change;
        }
	}


	void heroes_take_action(){
		int hero_index, monster_index, action;
		// input
		cout << "Select a hero for this turn to attack or consume a potion:" << endl;
        cin >> hero_index;
        cout << "What would you want to do?(1)Normal attack 2)Spell Attack 3)Consume potion)" << endl;
        cin >> action;

        if(action == 1){
			// option 1: attack with weapon
           	int attack = this->heroes->attack(hero_index-1);
           	cout << "[ATTACK]" << attack << endl;
			cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << endl;
			int monster_index;
			cin >> monster_index;
			this->monsters->getAttacked(monster_index - 1, attack);
			
		}else if(action == 2){	
			// option 2: attack with spell
			cout << "Select a spell to use:" << endl;
			std::cout << "SPELL LIST:\n--------------------"<<std::endl;
			for(int i = 0; i < this->heroes->spells.size(); i++){
				Spell* sp = heroes->spells.at(i);
               	cout << i + 1 << ")";
				sp->print();
			}
			int spell_index;
			cin >> spell_index;
			cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << endl;
			cin >> monster_index;
			Spell* sp = heroes->spells[spell_index - 1];
			int attack_power = heroes->attack(hero_index - 1, sp);
			this->monsters->getAttacked(monster_index - 1,attack_power);
			//this->monsters->getAttacked(monster_index - 1,sp);

		}else if(action == 3){
			// option 3: drink potion


		}
	}


public:

    Battle(heroe_squad* heroes,  monsters_squad* monsters)
    :heroes(heroes), monsters(monsters) {
        std::cout << "A battle is about to start!" << std::endl;
    }

    // actual battle
    bool battle(){  // the main function of the battle, everyhting happens in here
        //battle loop
        for(int round = 1; (!heroes_are_dead() && !monsters_are_dead()); round++){
            
			std::cout << "ROUND: " << round << std::endl;
			heroes_change_armor();
			heroes_change_weapon();
			heroes_take_action();	// attack with spell, attack with weapon, use potion

            // pc's turn
            for (int i = 0; i < monsters->get_monsters_num(); i++){
                if (monsters->monsters[i]->getHealth() != 0){
                    // every monster does something if its not dead
                    // i will figure out later what
                    this->heroes->getAttacked(monsters->monsters[i]->attack());
                    break;
                }
				// also update everything
            }
        }
        // end of battle
        return monsters_are_dead(); 
    }


};

