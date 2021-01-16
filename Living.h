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
			cout << "Name: " << this->name << endl;
			cout << "Level: " << this->level << endl;
			cout << "State: ";
			if(faint == 0)
				cout << "Currently In Good shape!" << endl;
			else
				cout << "Faint,He Is Currently Not Available!" << endl;	
		}
		
		bool isFaint() const{
			return this->faint;
		}
};

class Hero : public Living{
	protected:
		int magicPower;
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
			magicPower(magicPowerI), strength(strengthI), dexterity(dexterityI), agility(agilityI), experience(0), experienceForLevelUp(30), numOfItems(0), currentHealth(healthPowerI), armInUse(NULL) {
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
			int totalAttack;
			totalAttack = spell_->damage_to_do(this->dexterity);
			return totalAttack;
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
			cout << "Current Health: " << this->currentHealth << endl;
			cout << "Strength: " << this->strength << endl;
			cout << "Dexterity: " << this->dexterity << endl;
			cout << "Agility: " << this->agility << endl; 
		}
};

class Warrior : public Hero{
	public:
		Warrior(string nameI) : Hero(nameI,100,80,4,1,3) {
			cout << "[DEBUG] Warrior created!" << endl;
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
			cout << "[DEBUG] Sorcerer created!" << endl;
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
			cout << "[DEBUG] Paladin created!" << endl;
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
//		list<FireSpell*> fireSpells;
//		list<IceSpell*> iceSpells;
//		list<LightingSpell*> lightSpells;
	public:
		Monster(string nameI, int healthPowerI, int level, int attackMaxI, int attackMinI, int deffenceI ,double probOfDogdeI) :
			Living(nameI, healthPowerI + 0.1 * level,level), attackMax(attackMaxI), attackMin(attackMinI), deffence(deffenceI), probOfDogde(probOfDogdeI){}  		
		
		int getHealth(){
			return this->healthPower;
		}
		
		int attack(){
			srand((unsigned int) time(NULL));
			int attack = rand() % attackMax + attackMin;
			return attack;
		}
		
		void getAttacked(int attackPoints){
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
			}
			cout << "Current health of " << this->name << " is " << this->currentHealth << endl;
		}
		
		void getAttacked(FireSpell* spell, int attackPoints){
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
			}
			cout << "Current health of " << this->name << " is " << this->currentHealth << endl; 	
		
//			for(int i = 0; i < fireSpells.size(); i++){
//				if(spell. <= fireSpells[i])
//			}
		}
		
		virtual void print(){
			cout << "======== MONSTER STATS ============" << endl;
			Living::print();
			cout << "Current Health: " << this->currentHealth << endl; 
		}
};

class Dragon : public Monster{
	public:
		Dragon(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.9 * level, attackMinI + 1.9 * level, defenceI + 1.2 * level, probOfDogdeI + 0.05 * level) {
				cout << "[DEBUG] dragon created" << endl;			
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
				cout << "[DEBUG] exosceleton created" << endl;
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
				cout << "[DEBUG] spirit created" << endl;
			}
	void print(){
			Monster::print();
			cout << "Class: Spirit" << endl;
		}		
};
