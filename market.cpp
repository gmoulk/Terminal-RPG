#include <iostream>
#include "market.h"
#include "Items_and_spells.h"
#include "battle.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>

int const max_weapons = 10;
int const max_armors = 11;
int const max_spells = 12;
int const max_potions = 15;

market::market(heroe_squad* hs){
	srand((unsigned) time(NULL));
	int num_of_weapons = rand() % max_weapons;
	int num_of_armors = rand() % max_armors;
	int num_of_spells = rand() % max_spells;
	int num_of_potions = rand() % max_potions;
	ifstream in("weapons.txt");
	if(!in) {
    	cout << "Cannot open input file of weapons.\n";
    	exit(1);
  	}
  	
	ifstream in2("armor.txt");
	if(!in2) {
    	cout << "Cannot open input file of armors.\n";
    	exit(1);
  	}
  	
	ifstream in3("spells.txt");
	if(!in3) {
    	cout << "Cannot open input file of spells.\n";
    	exit(1);
  	}
	  
	ifstream in4("Potions.txt");
	if(!in4) {
    	cout << "Cannot open input file of potions.\n";
    	exit(1);
  	}
	for(int i = 0; i < num_of_weapons; i++){
		in.clear();
		in.seekg(0);
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
					if(j == 2)
						name = string(token1);
					else if(j == 4)
						level = atoi(token1);	
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
	}
			
	for(int i = 0; i < num_of_armors; i++){
		in2.clear();
		in2.seekg(0);
  		char str[255];
  		int armor_num = rand() % max_armors;
		for (int i = 0 ; i < armor_num * 5 ; i++){ 
    		in2.ignore(255,'\n');
    	}
		int j = 1;
		string name;
		int level;
		double price;
		double damageRed;
  		while(in2) {		 
    		in2.getline(str, 255);  // delim defaults to '\n'
    		char* token1 = strtok(str,":");				
			do{   	
				if(j % 2==0){
					if(j == 2)
						name = string(token1);
					else if(j == 4)
						level = atoi(token1);
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
	}
			
	for(int i = 0; i < num_of_spells; i++){
		in3.clear();
		in3.seekg(0);
  		char str[255];
  		int spell_num = rand() % max_spells;
		for (int i = 0 ; i < spell_num * 9 ; i++){ 
    		in3.ignore(255,'\n');
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
  		while(in3) {		 
    		in3.getline(str, 255);  // delim defaults to '\n'
    		char* token1 = strtok(str,":");				
			do{   	
				if(j % 2==0){
					if(j == 2){
						class_ = string(token1);
						cout << "DEBUG " << class_ << endl;
					}
					else if(j == 4)
						name = string(token1);
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
		else if(class_ == "IceSpell"){
			IceSpell* sp = new IceSpell(level,mana,name,stat,price,damageM,damageL);
			iceSpells.push_back(sp);
		}
		else{
			LightingSpell* sp = new LightingSpell(level,mana,name,stat,price,damageM,damageL);
			lightSpells.push_back(sp);
		}										
	}
			
	for(int i = 0; i < num_of_potions; i++){
		in4.clear();
		in4.seekg(0);		
  		char str[255];
  		int spell_num = rand() % max_spells;
		for (int i = 0 ; i < spell_num * 6 ; i++){ 
    		in4.ignore(255,'\n');
    	}
		int j = 1;
		string name;
		int level;
		double price;		
		double stat;
		int class_;				
  		while(in4) {		 
    		in4.getline(str, 255);  // delim defaults to '\n'
    		char* token1 = strtok(str,":");				
			do{   	
				if(j % 2==0){
					if(j == 2)
						name = string(token1);
					else if(j == 4)
						level = atoi(token1);
					else if(j == 6)
						price = atof(token1);	
					else if(j == 8)
						stat = atof(token1);
					else if(j == 10)			
						class_ = atoi(token1);			
				}
				j++;
				token1 = strtok(NULL,"\n");
			}while(token1 != NULL);
					
  		}
		Potion* pt = new Potion(level,price,name,stat,class_);
		potions.push_back(pt);									
	}
	this->hs = hs;
	in.close();
	in2.close();
	in3.close();
	in4.close();
}

void market::print(){
	cout << "==== MARKET ====" << endl;
	this->printWeapons();
	this->printArmor();
	this->printSpells();
}

void market::printWeapons(){
	cout << "==== WEAPONS ====" << endl;
	for(int i = 0; i < weapons.size(); i++){
		cout << i + 1 << ")" << endl;
		Weapon* wp = weapons[i];
		wp->print();
	}
}

void market::printArmor(){
	cout << "==== ARMOR ====" << endl;
	for(int i = 0; i < armors.size(); i++){
		cout << i + 1 << ")" << endl;
		Armor* ar = armors[i];
		ar->print();
	}
}

void market::printSpells(){
	cout << "==== SPELLS ====" << endl;
	cout << "==== ICE SPELLS ====" << endl;
	for(int i = 0; i < iceSpells.size(); i++){
		cout << i + 1 << ")" << endl;
		IceSpell* sp = iceSpells[i];
		sp->print();
	}
	cout << "==== FIRE SPELLS ====" << endl;
	for(int i = 0; i < fireSpells.size(); i++){
		cout << i + 1 << ")" << endl;
		FireSpell* sp = fireSpells[i];
		sp->print();
	}
	cout << "==== LIGHTING SPELLS ====" << endl;
	for(int i = 0; i < lightSpells.size(); i++){
		cout << i + 1 << ")" << endl;
		LightingSpell* sp = lightSpells[i];
		sp->print();
	}
}

void market::printPotion(){
	cout << "======= POTIONS =======" << endl;
	for(int i = 0; i < potions.size(); i++){
		cout << i + 1 << ")" << endl;
		Potion* pt = potions[i];
		pt->print();
	}
}


void market::buy(){
	int buyOption = 5;
			cout << "Would you like to buy a weapon(1), an armor(2), a spell(3), a potion(4) : " << endl;
			while(buyOption > 4){
				cin >> buyOption;
				cout << "Would you like to buy a weapon(1), an armor(2), a spell(3) : " << endl;
			}
			if(buyOption == 1 && this->weapons.size() != 0){
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
			else if(buyOption == 2 && this->armors.size() != 0){
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
			else if(buyOption == 3){
				this->printSpells();
				cout << "What spell would you like to buy?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
				int spellType = 4;
				while(spellType > 3 || spellType < 0){
					cin >> spellType ;
					cout << "What spell would you like to buy?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
				}
				int spellOption;
				if(spellType == 1 && this->iceSpells.size() != 0){
					for(int i = 0; i < iceSpells.size(); i++){
						cout << i + 1 << ")" << endl;
						Spell* sp = iceSpells[i];
						sp->print();
					}
					cout << "Choose the spell you want to buy range from 1 to " << iceSpells.size() << " or 0 to cancel" << endl;
					cin >> spellOption;
					if(spellOption > 0 && spellOption <= iceSpells.size()){
						if(hs->buy(this->iceSpells[spellOption - 1])){
							iceSpells.erase(iceSpells.begin() + spellOption - 1);
						}
					}
				}
				else if(spellType == 2 && this->fireSpells.size() != 0){
					for(int i = 0; i < fireSpells.size(); i++){
						cout << i + 1 << ")" << endl;
						Spell* sp = fireSpells[i];
						sp->print();
					}
					cout << "Choose the spell you want to buy range from 1 to " << fireSpells.size() << " or 0 to cancel" << endl;
					cin >> spellOption;
					if(spellOption > 0 && spellOption <= fireSpells.size()){
						if(hs->buy(this->fireSpells[spellOption - 1])){
							fireSpells.erase(fireSpells.begin() + spellOption - 1);
						}
					}
				}
				else if(this->lightSpells.size() != 0){
					for(int i = 0; i < lightSpells.size(); i++){
						cout << i + 1 << ")" << endl;
						Spell* sp = lightSpells[i];
						sp->print();
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
			else if(buyOption == 4 && this->potions.size() != 0){
				this->printPotion();
				cout << "What potion would you like to buy?(type from range 1 to " << this->potions.size() << " or 0 to cancel your action" << endl;
				int potionOption;
				cin >> potionOption;
				if(potionOption > 0){
					if(hs->buy(this->potions[potionOption - 1])){
						potions.erase(potions.begin() + potionOption - 1);
					}
				}
			}
			
}

void market::sell(){
	cout << "What would you like to sell: (1)Weapons (2)Armors (3)Potions (4)Ice Spells (5)Lighting Spells (6)Fire Spells [Press 0 or something else than the options to cancel]" << endl;
			int sellOption;
			cin >> sellOption;
			if(sellOption == 1){
				this->hs->printWeapons();
				cout << "Which Weapon would you like to sell?" << endl;
				int wpToSell;
				cin >> wpToSell;
				Weapon* wp = this->hs->sellWp(wpToSell);
				if(wp != NULL)
					this->weapons.push_back(wp);
			}
			else if(sellOption == 2){
				this->hs->printArmors();
				cout << "Which Armor would you like to sell?" << endl;
				int arToSell;
				cin >> arToSell;
				Armor* ar = this->hs->sellAr(arToSell);
				if(ar != NULL)
					this->armors.push_back(ar);
			}
			else if(sellOption == 3){
				this->hs->printPotions();
				cout << "Which Potion would you like to sell?" << endl;
				int ptToSell;
				cin >> ptToSell;
				Potion* pt = this->hs->sellPt(ptToSell);
				if(pt != NULL)
					this->potions.push_back(pt);			
			}
			else if(sellOption == 4){
				this->hs->printIceSpells();
				cout << "Which Ice Spell would you like to sell?" << endl;
				int isToSell;
				cin >> isToSell;
				IceSpell* is = this->hs->sellIs(isToSell);
				if(is != NULL)
					this->iceSpells.push_back(is);			
			}
			else if(sellOption == 5){
				this->hs->printLightingSpells();
				cout << "Which Lighting Spell would you like to sell?" << endl;
				int lsToSell;
				cin >> lsToSell;
				LightingSpell* ls = this->hs->sellLs(lsToSell);
				if(ls != NULL)
					this->lightSpells.push_back(ls);			
			}
			else if(sellOption == 6){
				this->hs->printFireSpells();
				cout << "Which Fire Spell would you like to sell?" << endl;
				int fsToSell;
				cin >> fsToSell;
				FireSpell* fs = this->hs->sellFs(fsToSell);
				if(fs != NULL)
					this->fireSpells.push_back(fs);			
			}
}


void market::interact(){
	cout << "Welcome to the store!" << endl;
	cout << "Would you like to buy something?(1 = yes / 0 = no)" << endl;
	bool i_want_to_buy_sell;
	cin >> i_want_to_buy_sell;
	while(i_want_to_buy_sell){
		cout << "Your money: " << this->hs->getMoney() << endl;
		cout << "Would you like to buy(1) or sell(0)?(Warning with sell your items will be selled with half of their price)" << endl;
		bool buy;
		cin >> buy;
		if(buy){		
			this->buy();
		}else{
			this->sell();
		}
		cout << "Would you like to buy/sell something else?(1 = yes / 0 = no)" << endl;
		cin >> i_want_to_buy_sell;
	}
}

market::~market(){
	for(int i = 0; i < armors.size(); i++)
		delete armors[i];
	for(int i = 0; i < weapons.size(); i++)
		delete weapons[i];
	for(int i = 0; i < iceSpells.size(); i++)
		delete iceSpells[i];
	for(int i = 0; i < fireSpells.size(); i++)
		delete fireSpells[i];
	for(int i = 0; i < lightSpells.size(); i++)
		delete lightSpells[i];
	for(int i = 0; i < potions.size(); i++)
		delete potions[i];									
}
