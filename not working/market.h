#pragma once
#include <iostream>
#include "Items_and_spells.h"
#include "battle.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
using namespace std;

int const max_weapons = 10;
int const max_armors = 11;
int const max_spells = 12;

class market{
	private:
		vector<Armor*> armors;
		vector<Weapon*> weapons;
		vector<IceSpell*> iceSpells;
		vector<FireSpell*> fireSpells;
		vector<LightingSpell*> lightSpells;
		vector<Potion*> potions;
		heroe_squad* hs;
	public:
		market(heroe_squad* hs){
			srand((unsigned) time(NULL));
			int num_of_weapons = rand() % max_weapons;
			int num_of_armors = rand() % max_armors;
			int num_of_spells = rand() % max_spells;
			//Max potions
			for(int i = 0; i < num_of_weapons; i++){
				ifstream in("weapons.txt");

				if(!in) {
    				cout << "Cannot open input file.\n";
    				exit(1);
  				}

  				char str[255];
  				int weap_num = rand() % max_weapons;
				for (int i = 0 ; i < weap_num * 6 ; i++){ 
    				in.ignore(255,'\n');
    			}
				int j = 1;
				string name;
				int level;
				float price;
				float damage;
				bool isTwoHanded;
  				while(in) {		 
    				in.getline(str, 255);  // delim defaults to '\n'
    				char* token1 = strtok(str,":");				
						do{   	
						if(j % 2==0){
							if(j == 2){
								name = string(token1);
								cout << "[DEBUG] NAME " << name << endl;
							}
							else if(j == 4){
								level = atoi(token1);
								cout << "[DEBUG] LEVEL " << level << endl;
							}
								
							else if(j == 6)
								price = atof(token1);	
							else if(j == 8)
								damage = atof(token1);
							else if(j == 10)
								isTwoHanded = atoi(token1);				
						}
					j++;
					token1 = strtok(NULL,"\n");
					}while(token1 != NULL);
					
  				}
				  	Weapon* wp = new Weapon(level,price,name,damage,isTwoHanded);
					weapons.push_back(wp);	
  					in.close();
			}
			
			for(int i = 0; i < num_of_armors; i++){
				ifstream in("armor.txt");

				if(!in) {
    				cout << "Cannot open input file.\n";
    				exit(1);
  				}

  				char str[255];
  				int armor_num = rand() % max_armors;
				for (int i = 0 ; i < armor_num * 5 ; i++){ 
    				in.ignore(255,'\n');
    			}
				int j = 1;
				string name;
				int level;
				float price;
				float damageRed;
  				while(in) {		 
    				in.getline(str, 255);  // delim defaults to '\n'
    				char* token1 = strtok(str,":");				
						do{   	
						if(j % 2==0){
							if(j == 2){
								name = string(token1);
							}
							else if(j == 4){
								level = atoi(token1);
							}
							else if(j == 6)
								price = atof(token1);	
							else if(j == 8)
								damageRed = atof(token1);			
						}
					j++;
					token1 = strtok(NULL,"\n");
					}while(token1 != NULL);
					
  				}
				  	Armor* ar = new Armor(level,price,name,damageRed);
					armors.push_back(ar);	
  					in.close();				
			}
			
			for(int i = 0; i < num_of_spells; i++){
				ifstream in("spells.txt");

				if(!in) {
    				cout << "Cannot open input file.\n";
    				exit(1);
  				}

  				char str[255];
  				int spell_num = rand() % max_spells;
				for (int i = 0 ; i < spell_num * 9 ; i++){ 
    				in.ignore(255,'\n');
    			}
				int j = 1;
				string class_;
				string name;
				int level;
				float price;
				int mana;
				float damageL;
				float damageM;
				float stat;
  				while(in) {		 
    				in.getline(str, 255);  // delim defaults to '\n'
    				char* token1 = strtok(str,":");				
						do{   	
						if(j % 2==0){
							if(j == 2){
								class_ = string(token1);
							}
							else if(j == 4){
								name = string(token1);
							}
							else if(j == 6)
								level = atoi(token1);	
							else if(j == 8)
								price = atoi(token1);
							else if(j == 10)			
								mana = atoi(token1);
							else if(j == 12)
								damageL = atof(token1);
							else if(j == 14)
								damageM = atof(token1);
							else if( j == 16)
								stat = atof(token1);			
						}
					j++;
					token1 = strtok(NULL,"\n");
					}while(token1 != NULL);
					
  				}
  					if(class_ == "FireSpell"){
						FireSpell* sp = new FireSpell(level,mana,name,stat,price,damageM,damageL);
					  	fireSpells.push_back(sp);
					  }
					if(class_ == "IceSpell"){
						IceSpell* sp = new IceSpell(level,mana,name,stat,price,damageM,damageL);
						iceSpells.push_back(sp);
					}
					if(class_ == "LightingSpell"){
						LightingSpell* sp = new LightingSpell(level,mana,name,stat,price,damageM,damageL);
						lightSpells.push_back(sp);
					}						
  					in.close();				
			}
			this->hs = hs;
		}
		
		void print(){
			cout << "==== MARKET ====" << endl;
			this->printWeapons();
			this->printArmor();
			this->printSpells();
		}
		
		void printWeapons(){
			cout << "==== WEAPONS ====" << endl;
			for(int i = 0; i < weapons.size(); i++){
				cout << i + 1 << ")" << endl;
				Weapon* wp = weapons[i];
				wp->print();
			}
		}
		
		void printArmor(){
			cout << "==== ARMOR ====" << endl;
			for(int i = 0; i < armors.size(); i++){
				cout << i + 1 << ")" << endl;
				Armor* ar = armors[i];
				ar->print();
			}
		}
		
		void printSpells(){
			cout << "==== SPELLS ====" << endl;
			cout << "==== ICE SPELLS ====" << endl;
			for(int i = 0; i < iceSpells.size(); i++){
				cout << i + 1 << ")" << endl;
				Spell* sp = iceSpells[i];
				sp->print();
			}
			cout << "==== FIRE SPELLS ====" << endl;
			for(int i = 0; i < fireSpells.size(); i++){
				cout << i + 1 << ")" << endl;
				Spell* sp = fireSpells[i];
				sp->print();
			}
			cout << "==== LIGHTING SPELLS ====" << endl;
			for(int i = 0; i < lightSpells.size(); i++){
				cout << i + 1 << ")" << endl;
				Spell* sp = lightSpells[i];
				sp->print();
			}
		}
		
		void interact(){
			cout << "Welcome to the store!" << endl;
			cout << "Would you like to buy something?(1 = yes / 0 = no)" << endl;
			bool i_want_to_buy;
			cin >> i_want_to_buy;
			while(i_want_to_buy){				
				int buyOption = 4;
				cout << "Would you like to buy a weapon(1), an armor(2), a spell(3) : " << endl;
				while(buyOption > 3){
					cin >> buyOption;
					cout << "Would you like to buy a weapon(1), an armor(2), a spell(3) : " << endl;
				}
				if(buyOption == 1){
					this->printWeapons();
					cout << "What weapon would you like to buy?(type from range 1 to " << this->weapons.size() << " or 0 to cancel your action" << endl;
					int weaponOption;
					cin >> weaponOption;
					if(weaponOption > 0){
						if(hs->buy(this->weapons[weaponOption - 1])){
							weapons.erase(weapons.begin() + weaponOption - 1);
						}
					}
				}
				if(buyOption == 2){
					this->printArmor();
					cout << "What armor would you like to buy?(type from range 1 to " << this->armors.size() << " or 0 to cancel your action" << endl;
					int armorOption;
					cin >> armorOption;
					if(armorOption > 0){
						if(hs->buy(this->armors[armorOption - 1])){
							armors.erase(armors.begin() + armorOption - 1);
						}
					}
				}
				if(buyOption == 3){
					this->printSpells();
					cout << "What spell would you like to buy?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
					int spellType = 4;
					while(spellType > 3 || spellType < 0){
						cin >> spellType ;
						cout << "What spell would you like to buy?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
					}
					int spellOption;
					if(spellType == 1){
						for(int i = 0; i < iceSpells.size(); i++){
							cout << i + 1 << ")" << endl;
							Spell* sp = iceSpells[i];
							sp->print();
							i++;
						}
						cout << "Choose the spell you want to buy range from 1 to " << iceSpells.size() << " or 0 to cancel" << endl;
						cin >> spellOption;
						if(spellOption > 0 && spellOption <= iceSpells.size()){
							if(hs->buy(this->iceSpells[spellOption - 1])){
								iceSpells.erase(iceSpells.begin() + spellOption - 1);
							}
						}
					}
					else if(spellType == 2){
						for(int i = 0; i < fireSpells.size(); i++){
							cout << i + 1 << ")" << endl;
							Spell* sp = iceSpells[i];
							sp->print();
							i++;
						}
						cout << "Choose the spell you want to buy range from 1 to " << fireSpells.size() << " or 0 to cancel" << endl;
						cin >> spellOption;
						if(spellOption > 0 && spellOption <= fireSpells.size()){
							if(hs->buy(this->fireSpells[spellOption - 1])){
								fireSpells.erase(fireSpells.begin() + spellOption - 1);
							}
						}
					}
					else{
						for(int i = 0; i < lightSpells.size(); i++){
							cout << i + 1 << ")" << endl;
							Spell* sp = iceSpells[i];
							sp->print();
							i++;
						}
						cout << "Choose the spell you want to buy range from 1 to " << lightSpells.size() << " or 0 to cancel" << endl;
						cin >> spellOption;
						if(spellOption > 0 && spellOption <= lightSpells.size()){
							if(hs->buy(this->lightSpells[spellOption - 1])){
								lightSpells.erase(lightSpells.begin() + spellOption - 1);
							}
						}
					}
				}
				cout << "Would you like to buy something?(1 = yes / 0 = no)" << endl;
				cin >> i_want_to_buy;
			}
		}
};
