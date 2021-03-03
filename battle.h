#pragma once
#include <iostream>
#include "living.h"
#include "Items_and_spells.h"
#include <string>
#include <vector>

using namespace std;

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

	Spell* useSpells(int type);


	IceSpell* useIceSpells(){  return dynamic_cast<IceSpell*>(useSpells(ice));	}
	FireSpell* useFireSpells(){	return dynamic_cast<FireSpell*>(useSpells(fire)); }
	LightingSpell* useLightSpells(){	return dynamic_cast<LightingSpell*>(useSpells(lighting)); }
	
	// inventory functions
	
	void change_armor(int hero_index, int option);
	
	void change_weapon(int hero_index, int option);
	
	// attack function

	int attack(int i){
		return this->heroes[i]->attack();
	}
	 
	int attack(int i, Spell* sp){
		return this->heroes[i]->attack(sp);	
	} 
	
	void getAttacked(int attackPoints);


 public:

	heroe_squad(Hero* hero1, Hero* hero2=NULL, Hero* hero3=NULL, int _number_of_heroes = 1)
	:number_of_heroes(_number_of_heroes), money(200){
		heroes[0] = hero1;
		heroes[1] = hero2;
		heroes[2] = hero3;
	}

	~heroe_squad();
	
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
	


	void checkInvetory();
    
	// buy functions
	
    bool buy(Item* item, int type);

    bool buy(Weapon* arm)	{	return buy(arm, weapon);	}
	bool buy(Armor* arm)	{	return buy(arm, armor);		}
	bool buy(Potion* arm)	{	return buy(arm, potion);	}
	


    bool buySpell(Spell* sp, int type){
        if(sp->getPrice() <= this->money){
			this->money -= sp->getPrice();
			this->spells[type].push_back(sp);
			return 1;
		}
		return 0;
    }
	
	bool buy(IceSpell* sp)		{	return buySpell(sp, ice);		 }
	bool buy(FireSpell* sp)		{	return buySpell(sp, fire);		 }
	bool buy(LightingSpell* sp)	{	return buySpell(sp, lighting);	 }

	
	// sell functions
	Item* sellItem(int i, int type);


	Weapon* sellWp(int i){	return dynamic_cast<Weapon*> (sellItem(i, weapon));	}
	Armor*  sellAr(int i){	return dynamic_cast<Armor*>  (sellItem(i, armor));	}
	Potion* sellPt(int i){	return dynamic_cast<Potion*> (sellItem(i, potion));	}
	


	Spell* sellSpell(int i, int type);
	

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
	

	int averageLevel();
	

	int getMoney(){	return money; }
	
	void battleLost(){
		cout << "Battle lost!" << endl;
		this->money = this->money / 2;
	}
	
	void battleWon(int numOfMonsters);


	void change_armor();

	void change_weapon();

	void usePotion(int hero_index);
	
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
	

	void getInfected(int index,Spell* sp);
	
	
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

	void heroes_take_action();


public:

    Battle(heroe_squad* heroes,  monsters_squad* monsters)
    :heroes(heroes), monsters(monsters) {
        std::cout << "A battle is about to start!" << std::endl;
    }
	
	void displayStats() const;
	

    // actual battle
    bool battle();
    
    ~Battle(){
    	delete this->monsters;
	}
};
