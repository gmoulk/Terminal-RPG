#pragma once
#include <iostream>
using namespace std;

class Living{
	protected:
		string name;
		int level;
		int healthPower;
	public:
		Living(string nameI,int healthPowerI, int levelI) : name(nameI), healthPower(healthPowerI), level(levelI) {}	
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
		//Characteristics that affect battle phase
	public:
		Hero(string nameI, int healthPowerI,int magicPowerI, int strengthI, int dexterityI, int agilityI) : Living(nameI,healthPowerI,0) , 
			magicPower(magicPowerI), strength(strengthI), dexterity(dexterityI), agility(agilityI), money(0), experience(0), experienceForLevelUp(30) {}
		virtual void levelUp() = 0;

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
};

class Dragon : public Monster{
	public:
		Dragon(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.9 * level, attackMinI + 1.9 * level, defenceI + 1.2 * level, probOfDogdeI + 0.05 * level) {
				cout << "[DEBUG] dragon created" << endl;			
			}
};

class Exosceleton : public Monster{
	public:
		Exosceleton(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.2 * level, attackMinI + 1.2 * level, defenceI + 1.9 * level, probOfDogdeI + 0.05 * level) {
				cout << "[DEBUG] exosceleton created" << endl;
			}
};

class  Spirit : public Monster{
	public:
		Spirit(string nameI, int level, int healthPowerI,int attackMaxI, int attackMinI, int defenceI, double probOfDogdeI):
			Monster(nameI, level, healthPowerI, attackMaxI + 1.2 * level, attackMinI + 1.2 * level, defenceI + 1.2 * level, probOfDogdeI + 0.08 * level) {
				cout << "[DEBUG] spirit created" << endl;
			}
};
