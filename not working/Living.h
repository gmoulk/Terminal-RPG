#pragma once
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <list>
#include "Items_and_spells.h"
using namespace std;

class Living{
	protected:
		string name;
		int level;
		int healthPower;
		bool faint;
		int currentHealth;
	public:
		Living(string nameI,int healthPowerI, int levelI) : name(nameI), healthPower(healthPowerI), level(levelI), faint(0) , currentHealth(healthPower) {}	
	
		string getName(){
			return this->name;
		}
		virtual void print(){
			cout << "[Name: " << this->name << "], ";
			cout << "[Level: " << this->level << "], ";
			cout << "[State: ";
			if(faint == 0)
				cout << "In Good shape!]" << endl;
			else
				cout << "Currently Not Available!]" << endl;	
		}
		
		bool isFaint() const{
			return this->faint;
		}
		
		virtual void update() = 0;
};

class Hero : public Living{
	protected:
		int magicPower;
		int currentMagicPower;
		int strength;
		int dexterity;
		int agility;
		int experience;
		int experienceForLevelUp;
		int currentHealth;
		Weapon* wpInUse1;
		Weapon* wpInUse2;
		Armor* armInUse;
		int numOfItems;
		//Characteristics that affect battle phase
		
	public:
		Hero(string nameI, int healthPowerI,int magicPowerI, int strengthI, int dexterityI, int agilityI) : Living(nameI,healthPowerI,0) , 
			magicPower(magicPowerI), currentMagicPower(magicPowerI),strength(strengthI), dexterity(dexterityI), agility(agilityI), experience(0), experienceForLevelUp(30), numOfItems(0), currentHealth(healthPowerI), armInUse(NULL) {
				wpInUse1 = NULL;
				wpInUse2 = NULL;
			}
		
		int getcurrentHealth(){
			return this->currentHealth;
		}
		
		virtual void levelUp() = 0;
		
		int attack(){
			int totalAttack = 0;			
			if(this->wpInUse1 != NULL)
				totalAttack += this->wpInUse1->weapon_damage();				
			if(this->wpInUse2 != NULL)
				totalAttack += this->wpInUse2->weapon_damage();
			totalAttack += this->strength;
			
			return this->strength;
		}
		
		int attack(Spell* spell_){
			int currentMagic = this->currentMagicPower - spell_->get_mana();
			if(currentMagic >= 0){
				int totalAttack;
				totalAttack = spell_->damage_to_do(this->dexterity);
				this->currentMagicPower = currentMagic;
				return totalAttack;
			}
		}
		
		void getAttacked(int attackPoints){
			srand((unsigned int) time(NULL));
			double dogde = (double)rand() / RAND_MAX;
			if((0.02 * this->agility) > dogde)
				return;
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
		
		Item* equip(Armor* armToEquip){
			Item* temp = this->armInUse;
			this->armInUse = armToEquip;
			return temp;
		}
		
		Item** equip(Weapon* wepToEquip){
			Weapon** arrayOfWep = new Weapon*[2];
			if((this->wpInUse1 != NULL && wepToEquip->numOfHands() == 1 ) || (this->wpInUse1 == NULL && this->wpInUse2 == NULL)){
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
		}
	
		virtual void print(){
			cout << "======== HERO STATS ============" << endl;
			Living::print();
			cout << "[Current Health: " << this->currentHealth << "], ";
			cout << "[Current Magic Power: " << this->currentMagicPower <<"], ";
			cout << "[Strength: " << this->strength << "], ";
			cout << "[Dexterity: " << this->dexterity << "], ";
			cout << "[Agility: " << this->agility << "] " << endl; 
		}
		
		void update(){
			this->currentHealth += this->currentHealth*0.05;
			if(this->currentHealth >= this->healthPower)
				this->currentHealth = this->healthPower;
			this->currentMagicPower += this->currentMagicPower*0.05;
			if(this->currentMagicPower >= this->magicPower)
				this->currentMagicPower = this->magicPower;
		}
		
		int getLevel(){
			return this->level;
		}
		
		void getExperience(int numOfMonsters){
			if(this->level < 1)
				this->experience += 0,4*this->experience*numOfMonsters;
			if(this->level < 4)
				this->experience += 0,2*this->experience*numOfMonsters;
			else
				this->experience += 0,1*this->experience*numOfMonsters;
			
			if(this->experience >= this->experienceForLevelUp){
				this->levelUp();
			}		
		}
		
		void use_potion(Potion* potion){ //  which to icnrease?
			
			int stat_to_increase = potion->get_stat_to_increase();
			/* 			1 = strength		2 = dexterity		3 = agility			*/
			if (stat_to_increase == 1){
				std::cout << "Strength increased by " << potion->use(this->strength) << " points." << std::endl;
			}else if(stat_to_increase == 2){
				std::cout << "Dexterity increased by " << potion->use(this->dexterity) << " points." << std::endl;
			}else if(stat_to_increase == 3){
				std::cout << "Agility increased by " << potion->use(this->agility) << " points." << std::endl;
			}
			// after usage, potion must be deleted from inventory
		}
};

class Warrior : public Hero{
	public:
		Warrior(string nameI) : Hero(nameI,100,80,4,1,3) {
		}
		
		void levelUp(){
			cout << this->name << " has been leveled up!" << endl;
			this->strength += 3;
			this->agility += 2;
			this->dexterity += 1;
			this->level++;
			this->experience = this->experienceForLevelUp - this->experience;
			this->experienceForLevelUp += 1.2 * this->level;
		}
		
		void print(){
			Hero::print();
			cout << "Class: Warrior" << endl; 
		}
};

class Sorcerer : public Hero{
	public:
		Sorcerer(string nameI) : Hero(nameI,70,110,1,4,4) {
		}
		void levelUp(){
			cout << this->name << " has been leveled up!" << endl;
			this->strength += 1;
			this->agility += 2;
			this->dexterity += 3;
			this->level++;
			this->experience = this->experienceForLevelUp - this->experience;
			this->experienceForLevelUp += 1.2 * this->level;
		}
		
		void print(){
			Hero::print();
			cout << "Class: Sorcerer" << endl; 
		}
};

class Paladin : public Hero{
	public:
		Paladin(string nameI) : Hero(nameI,90,95,3,3,1) {
		}
		
		void levelUp(){
			cout << this->name << " has been leveled up!" << endl;
			this->strength += 3;
			this->agility += 1;
			this->dexterity += 2;
			this->level++;
			this->experience = this->experienceForLevelUp - this->experience;
			this->experienceForLevelUp += 1.2 * this->level;
		}
		
		void print(){
			Hero::print();
			cout << "Class: Sorcerer" << endl; 
		}
};

class Monster : public Living{
	protected:
		int attackMax;
		int attackMin;
		int deffence;
		double probOfDogde;
		Effect* effect;
// 		only one effect per monster

	public:
		Monster(string nameI, int level, int healthPowerI, int attackMaxI, int attackMinI, int deffenceI ,double probOfDogdeI) :
			Living(nameI, healthPowerI + 0.1 * level,level), attackMax(attackMaxI), attackMin(attackMinI), deffence(deffenceI), probOfDogde(probOfDogdeI), effect(NULL){}  		
		
		int getcurrentHealth(){
			return this->currentHealth;
		}
		
		int attack(){
			srand((unsigned int) time(NULL));
			if(attackMax <= 0)
				return 0;
			int attack = rand() % attackMax + attackMin;
			cout << "MONSTER ATTACK IS " << attack << endl;
			return attack;
		}
		
		void getAttacked(int attackPoints){
			if(this->currentHealth == 0){
				cout << "Stop " << this->name << " is already faint!" << endl;
				return;
			}
			srand((unsigned int) time(NULL));
			double dogde = (double)rand() / RAND_MAX;
			if(dogde < probOfDogde)
				return;
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

		// getting attacked by a spell
		void getAttacked(int effect_type, int attackPoints){ 
			//(effect type) 1 = ice,  2 = fire, 3 = lighting, the way this information is given will probably change
			this->getAttacked(attackPoints);	
		}
		
		virtual void print(){
			cout << "======== MONSTER STATS ============" << endl;
			Living::print();
			cout << "[Current Health: " << this->currentHealth << "], " << endl; 
		}
		
		bool getInfected(FireSpell* sp){
			srand((unsigned) time(NULL));
			if(this->effect != NULL)
				delete this->effect;
			this->effect = new Fire_Effect(this->deffence,rand() % 5,sp->getRed());
			cout << "Infected by FireSpell!" << endl;
			this->effect->apply_effect();
		}
		
		bool getInfected(IceSpell* sp){
			srand((unsigned) time(NULL));
			if(this->effect != NULL)
				delete this->effect;
			this->effect = new Ice_Effect(this->attackMax,rand() % 5,sp->getRed());
			this->effect->apply_effect(); 
		}
		
		bool getInfected(LightingSpell* sp){
			srand((unsigned) time(NULL));
			if(this->effect != NULL)
				delete this->effect;
			this->effect = new Lighting_effect(this->probOfDogde,rand() % 5,sp->getRed());
			this->effect->apply_effect(); 
		}
		
		void update(){
			if(this->effect != NULL){
				if(this->effect->update()){
					cout << "Effect on!" << endl;
					this->effect->debug();
					return;	
				}
				else{
					cout << "The effect is over!" << endl;
					cout << "{Max attack} " << this->attackMax << endl;
					delete this->effect;	
					this->effect = NULL;				
				}
			}	
		}
};

class Dragon : public Monster{
	public:
		Dragon(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.9 * level, attackMinI + 1.9 * level, defenceI + 1.2 * level, probOfDogdeI + 0.05 * level) {			
			}
			
		void print(){
			Monster::print();
			cout << "Class: Dragon" << endl;
		}	
};

class Exosceleton : public Monster{
	public:
		Exosceleton(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.2 * level, attackMinI + 1.2 * level, defenceI + 1.9 * level, probOfDogdeI + 0.05 * level) {
			}
			
		void print(){
			Monster::print();
			cout << "Class: Exosceleton" << endl;
		}	
};

class  Spirit : public Monster{
	public:
		Spirit(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.2 * level, attackMinI + 1.2 * level, defenceI + 1.2 * level, probOfDogdeI + 0.08 * level) {
			}
	void print(){
			Monster::print();
			cout << "Class: Spirit" << endl;
		}		
};

