#include "living.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <list>
#include "Items_and_spells.h"
using namespace std;

void Living::print()const{
	cout << "Name: " << this->name << endl;
	cout << "Level: " << this->level << endl;
	cout << "HP: " << this->currentHealth << endl;
	cout << "State: ";
	if(faint == 0)
		cout << "Currently In Good shape!" << endl;
	else
		cout << "Faint,He Is Currently Not Available!" << endl;		
}

int Hero::attack(){
	int totalAttack = 0;			
	if(this->wpInUse1 != NULL)
		totalAttack += this->wpInUse1->weapon_damage();				
	if(this->wpInUse2 != NULL)
		totalAttack += this->wpInUse2->weapon_damage();
	totalAttack += this->strength;
			
	return totalAttack;
}

int Hero::attack(Spell* spell_){
	if(spell_->get_level() > this->level){
		cout << "Spell level is greater than hero level!" << endl;
		return 0;
	}
	int currentMagic = this->currentMagicPower - spell_->get_mana();
	if(currentMagic >= 0){
		int totalAttack;
		totalAttack = spell_->damage_to_do(this->dexterity);
		this->currentMagicPower = currentMagic;
		return totalAttack;
	}
	return 0;
}

void Hero::getAttacked(int attackPoints){
	srand((unsigned int) time(NULL));
	int dogde = rand() % RAND_MAX;
	if((2 * this->agility) > dogde){
		cout << "Monster attack dogded by " << this->name;
		return;
	}
	int attackFinal = attackPoints;	
	if(armInUse != NULL)	
		attackFinal = attackPoints * this->armInUse->get_damage_percentage();
	this->currentHealth -= attackFinal;
	if(this->currentHealth <= 0){
		cout << this->getName() << " faints!" << endl;
		this->currentHealth = 0;
		this->faint = 1;
	}
	cout << "Current health of " << this->name << " is " << this->currentHealth << endl;
}

Item* Hero::equip(Armor* armToEquip){
	if(armToEquip->getLevel() > this->level){
		cout << "The level of " << armToEquip->getName() << " is greater than hero " << this->name << endl;
		return armToEquip;
	}
	Item* temp = this->armInUse;
	this->armInUse = armToEquip;
	return temp;
}

Item** Hero::equip(Weapon* wepToEquip){
	Weapon** arrayOfWep = new Weapon*[2];
	for(int i = 0; i < 2; i++)
		arrayOfWep[i] = NULL;
	if(wepToEquip->getLevel() > this->level){
		cout << "The level of " << wepToEquip->getName() << " is greater than hero " << this->name << endl;
		arrayOfWep[0] = wepToEquip;
		arrayOfWep[1] = NULL;
		return (Item**) arrayOfWep;
	}
	//Needs change	
	if((this->wpInUse1 != NULL && wepToEquip->numOfHands() == 2 ) || (this->wpInUse1 == NULL && this->wpInUse2 == NULL)){
		arrayOfWep[0] = wpInUse1;
		arrayOfWep[1] = NULL;
		this->wpInUse1 = wepToEquip;
		return (Item**) arrayOfWep;
	}
	else if((wpInUse1 != NULL) && (wpInUse2 != NULL) && (wepToEquip->numOfHands() == 1)){
		cout << "Which weapon would you like to put in your inventory?" << endl;
		cout << "1)" << endl;
		wpInUse1->print();
		cout << "2)" << endl;
		wpInUse2->print();
		int option2;
		cin >> option2;
		if(option2 == 1){
			arrayOfWep[0] = wpInUse1;
			arrayOfWep[1] = NULL;
			this->wpInUse1 = wepToEquip;
			return (Item**) arrayOfWep;
		}
		else if(option2 == 2){
			arrayOfWep[0] = wpInUse2;
			arrayOfWep[1] = NULL;
			this->wpInUse2 = wepToEquip;
			return (Item**) arrayOfWep;
		}
	}
	else {
		arrayOfWep[0] = wpInUse1;
		this->wpInUse1 = wepToEquip;
		arrayOfWep[1] = this->wpInUse2;
		this->wpInUse2 = NULL; 
		return (Item**) arrayOfWep;
	}
	return (Item**) arrayOfWep;
}

void Hero::print(){
	cout << "======== HERO STATS ============" << endl;
	Living::print();
	cout << "Current Magic Power: " << this->currentMagicPower << endl;
	cout << "Strength: " << this->strength << endl;
	cout << "Dexterity: " << this->dexterity << endl;
	cout << "Agility: " << this->agility << endl; 
}

void Hero::update(){
	this->currentHealth += this->currentHealth*0.05;
	if(this->currentHealth >= this->healthPower)
		this->currentHealth = this->healthPower;
	this->currentMagicPower += this->currentMagicPower*0.05;
	if(this->currentMagicPower >= this->magicPower)
		this->currentMagicPower = this->magicPower;
}

void Hero::getExperience(int numOfMonsters){
	if(this->level < 1)
		this->experience += 0,4*this->experience*numOfMonsters;
	if(this->level < 4)
		this->experience += 0,2*this->experience*numOfMonsters;
	else
		this->experience += 0,1*this->experience*numOfMonsters;		
	if(this->experience >= this->experienceForLevelUp)
		this->levelUp();		
}

bool Hero::use_potion(Potion* potion){ //  which to icnrease?
	if(potion->getLevel() > this->level){
		cout << "Potion level is greater than hero level!" << endl;
		return false;
	}
	/* 			1 = strength		2 = dexterity		3 = agility			*/
	if (potion->get_stat_to_increase() == 1){
		std::cout << "Strength increased by " << potion->use(this->strength) << " points." << std::endl;
	}else if(potion->get_stat_to_increase() == 2){
		std::cout << "Dexterity increased by " << potion->use(this->dexterity) << " points." << std::endl;
	}else{
		std::cout << "Agility increased by " << potion->use(this->agility) << " points." << std::endl;
	}
	return true;
	// after usage, potion must be deleted from inventory
}

Weapon** Hero::takeOutWeapons(){
	bool wantToTakeOut;
	Weapon** retWp = new Weapon*[2];
	for(int i = 0; i < 2; i++)
		retWp[i] = NULL;
		if(this->wpInUse1 != NULL){
			cout << "Would you like to change:(1 = Yes / 0 = No)" << endl;
			this->wpInUse1->print();
			cin >> wantToTakeOut;
			if(wantToTakeOut){
				retWp[0] = this->wpInUse1;
				this->wpInUse1 = NULL;
			}
		}
			
		if(this->wpInUse2 != NULL){
			cout << "Would you like to change:(1 = Yes / 0 = No)" << endl;		
			this->wpInUse2->print();
			cin >> wantToTakeOut;
			if(wantToTakeOut){
				retWp[1] = this->wpInUse2;
				this->wpInUse2 = NULL;
			}
		}
			
		if(this->wpInUse2 != NULL && this->wpInUse1 == NULL){
			this->wpInUse1 = this->wpInUse2;
			this->wpInUse2 = NULL;
		}
	return retWp;
}

void Hero::levelUp(int extra_strength, int extra_agility, int extra_dexterity){
	cout << this->name << " has been leveled up!" << endl;
	this->strength	+= extra_strength;
	this->agility 	+= extra_agility;
	this->dexterity += extra_dexterity;
	this->level 	+= 1;
	this->experience = this->experienceForLevelUp - this->experience;
	this->experienceForLevelUp += 1.2 * this->level;
}

void Warrior::levelUp(){
	Hero::levelUp(3,3,1);
}

void Sorcerer::levelUp(){
	Hero::levelUp(1, 3, 3);
}

void Paladin::levelUp(){
	Hero::levelUp(3, 1, 3);
}

int Monster::attack(){
	srand((unsigned int) time(NULL));
	if(attackMax <= 0)
		return 0;
	int attack = rand() % attackMax + attackMin;
	return attack;
}

void Monster::getAttacked(int attackPoints){
	if(this->currentHealth == 0){
		cout << "Stop " << this->name << " is already faint!" << endl;
		return;
	}
	// DOGDE
	srand((unsigned int) time(NULL));
	int dogde =  rand() % 100;
	if(dogde < probOfDogde){
		std::cout << "Monster Dogded!\n"; 
		return;
	}
				
	int finalAttack = attackPoints - deffence;
	if(finalAttack <= 0)
		finalAttack = 0;
	currentHealth -= finalAttack;
	if(currentHealth <= 0){
		cout << this->name << " faints!" << endl;
		this->faint = 1;
		this->currentHealth = 0;
	}
	cout << "Current health of " << this->name << " is " << this->currentHealth << endl;
}

void Monster::print()const{
	cout << "======== MONSTER STATS ============" << endl;
	Living::print();
	cout << "Max Attack: " << this->attackMax << endl;
	cout << "Min Attack: " << this->attackMin << endl;
	cout << "Probability of dogde: " << this->probOfDogde << endl;
	if(effect != NULL){
		cout << "Monster is under effect!" << endl;
	}
}

void Monster::getInfected(FireSpell* sp){
	srand((unsigned) time(NULL));
	if(this->effect != NULL)
		delete this->effect;
	this->effect = new Effect(this->deffence,rand() % 5,sp->getRed());
	cout << "Infected by Fire Spell!" << endl;
	this->effect->apply_effect();
}

void Monster::getInfected(IceSpell* sp){
	srand((unsigned) time(NULL));
	if(this->effect != NULL)
		delete this->effect;
	this->effect = new Effect(this->attackMax,rand() % 5,sp->getRed());
	this->effect->apply_effect(); 
}

void Monster::getInfected(LightingSpell* sp){
	srand((unsigned) time(NULL));
	if(this->effect != NULL)
		delete this->effect;
	this->effect = new Effect(this->probOfDogde,rand() % 5,sp->getRed());
	this->effect->apply_effect(); 
}

void Monster::update(){
	this->currentHealth += 0.02 * this->currentHealth;
	if(this->currentHealth > this->healthPower)
		this->currentHealth = this->healthPower;
	if(this->effect != NULL){
		if(this->effect->update()){
			cout << "Effect on!" << endl;
			return;	
		}
		else{
			cout << "The effect is over!" << endl;
			delete this->effect;	
			this->effect = NULL;				
		}
	}
}
