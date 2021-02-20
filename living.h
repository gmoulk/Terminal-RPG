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
		
		virtual void print();
		
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
		
		int attack();
		
		int attack(Spell* spell_);
		
		void getAttacked(int attackPoints);
		
		Item* equip(Armor* armToEquip);
		
		Item** equip(Weapon* wepToEquip);
		
		Armor* takeOutArmor(){
			this->armInUse = NULL;
			return this->armInUse;
		}
		
		Weapon** takeOutWeapons();
	
		virtual void print();
		
		void update();
		
		int getLevel(){
			return this->level;
		}
		
		void getExperience(int numOfMonsters);
		
		bool use_potion(Potion* potion);
		
		void revive(){
			if(this->currentHealth == 0)
				this->currentHealth = this->healthPower / 2;
		}
		~Hero(){
			if(this->armInUse != NULL)
				delete armInUse;
			if(this->wpInUse1 != NULL)
				delete this->wpInUse1;
			if(this->wpInUse2 != NULL)
				delete this->wpInUse2;		
		}
};

class Warrior : public Hero{
	public:
		Warrior(string nameI) : Hero(nameI,100,80,6,3,5) {
		}
		
		void levelUp();
		
		void print(){
			Hero::print();
			cout << "Class: Warrior" << endl; 
		}
};

class Sorcerer : public Hero{
	public:
		Sorcerer(string nameI) : Hero(nameI,70,110,3,6,6) {
		}
		
		void levelUp();
		
		void print(){
			Hero::print();
			cout << "Class: Sorcerer" << endl; 
		}
};

class Paladin : public Hero{
	public:
		Paladin(string nameI) : Hero(nameI,90,95,5,5,3) {
		}
		
		void levelUp();
		
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
		int probOfDogde;  // at 100
		Effect* effect;
// 		only one effect per monster

	public:
		Monster(string nameI, int level, int healthPowerI, int attackMaxI, int attackMinI, int deffenceI ,int probOfDogdeI) :
			Living(nameI, healthPowerI + 0.1 * level,level), attackMax(attackMaxI), attackMin(attackMinI), deffence(deffenceI), probOfDogde(probOfDogdeI), effect(NULL){}  		
		
		int getcurrentHealth(){
			return this->currentHealth;
		}
		
		int attack();
		
		void getAttacked(int attackPoints);
		
		virtual void print();
		
		// infection functions 

		void getInfected(FireSpell* sp);
		
		void getInfected(IceSpell* sp);
		
		void getInfected(LightingSpell* sp);
		
		void update();
};

// FIX PROBODDODGE

class Dragon : public Monster{
	public:
		Dragon(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, int probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 4 * level, attackMinI + 4 * level, defenceI + 2 * level, probOfDogdeI + (5 * level)) {			
			}
			
		void print(){
			Monster::print();
			cout << "Class: Dragon" << endl;
		}	
};

class Exosceleton : public Monster{
	public:
		Exosceleton(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, int probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 2 * level, attackMinI + 2 * level, defenceI + 4 * level, probOfDogdeI + (5 * level)) {
			}
			
		void print(){
			Monster::print();
			cout << "Class: Exosceleton" << endl;
		}	
};

class  Spirit : public Monster{
	public:
		Spirit(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, int probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 2 * level, attackMinI + 2 * level, defenceI + 2 * level, probOfDogdeI + (9 * level)) {
			}
	void print(){
			Monster::print();
			cout << "Class: Spirit" << endl;
		}		
};

