#pragma once
#include <iostream>
#include <ctime>
#include <stdlib.h>
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
		Living(string nameI,int healthPowerI, int levelI) : name(nameI), healthPower(healthPowerI), level(levelI), faint(0) {}	
	
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
};

class Hero : public Living{
	protected:
		int magicPower;
		int strength;
		int dexterity;
		int agility;
		int money;
		int experience;
		int experienceForLevelUp;
		int currentHealth;
		Weapon* wpInUse;
		Armor* armInUse;
		Item* bag[20];
		int numOfItems;
		//Characteristics that affect battle phase
	public:
		Hero(string nameI, int healthPowerI,int magicPowerI, int strengthI, int dexterityI, int agilityI) : Living(nameI,healthPowerI,0) , 
			magicPower(magicPowerI), strength(strengthI), dexterity(dexterityI), agility(agilityI), money(0), experience(0), experienceForLevelUp(30), numOfItems(0), currentHealth(healthPowerI) {
				this->wpInUse = NULL;
				this->armInUse = NULL;
				for(int i = 0; i < 20; i++)
					bag[i] = NULL;
			}
		
		int getcurrentHealth(){
			return this->currentHealth;
		}
		
		virtual void levelUp() = 0;
		
		int attack(){
			int totalAttack = 0;
			if(this->wpInUse != NULL)
				totalAttack += this->wpInUse->weapon_damage();
			totalAttack += this->strength;
			return this->strength;
		}
		
		void getAttacked(int attackPoints){
			srand((unsigned int) time(NULL));
			double dogde = (double)rand() / RAND_MAX;
			if((0.02 * this->agility) > dogde)
				return;
			int attackFinal = attackPoints * this->armInUse->get_damage_percentage();
			this->currentHealth -= attackFinal;
			if(this->currentHealth <= 0){
				cout << this->getName() << " faints!" << endl;
				this->faint = 1;
			}
		}
		
		void equip(){
			if(numOfItems == 0){
				cout << "No items in the bag to use!" << endl;
				return;
			}
			cout << "Select one of the following to equip:";
			for(int i = 0; i < numOfItems; i++){
				cout << i + 1 << ")" << endl;
				bag[i]->print();
			}
			int option;
			cin >> option;
			bool legitOption = 0;
			do{
				if(option > 0 || option <= numOfItems + 1)
					legitOption = 1;
			}while(!legitOption);
			
			if(bag[option - 1]->itemClass() == 1){
				Item* temp_it = wpInUse;
				this->wpInUse = (Weapon*) bag[option - 1];
				bag[option - 1] = temp_it;
			}
			else if(bag[option - 1]->itemClass() == 2){
				Item* temp_it = armInUse;
				this->armInUse = (Armor*) bag[option - 1];
				bag[option - 1] = temp_it;
			}
			else{
				cout << "Using potion!" << endl;
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
	public:
		Monster(string nameI, int healthPowerI, int level, int attackMaxI, int attackMinI, int deffenceI ,double probOfDogdeI) :
			Living(nameI, healthPowerI,level), attackMax(attackMaxI), attackMin(attackMinI), deffence(deffenceI), probOfDogde(probOfDogdeI){}  		
		
		int getHealth(){
			return this->healthPower;
		}
		
		void getAttacked(int attackPoints){
			srand((unsigned int) time(NULL));
			double dogde = (double)rand() / RAND_MAX;
			if(dogde < probOfDogde)
				return;
			int finalAttack = attackPoints - deffence;
			healthPower -= finalAttack;	
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
