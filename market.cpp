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
		items[weapon].push_back(wp);	
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
		items[armor].push_back(ar);					
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
					if(j == 2)
						class_ = string(token1);
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
		Spell* sp;
  		if(class_ == "FireSpell"){
			sp = new FireSpell(level,mana,name,stat,price,damageM,damageL);
			spells[fire].push_back(sp);
		}
		else if(class_ == "IceSpell"){
			sp = new IceSpell(level,mana,name,stat,price,damageM,damageL);
			spells[ice].push_back(sp);
		}
		else{
			sp = new LightingSpell(level,mana,name,stat,price,damageM,damageL);
			spells[lighting].push_back(sp);
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
		items[potion].push_back(pt);									
	}
	this->hs = hs;
	in.close();
	in2.close();
	in3.close();
	in4.close();
}

void market::print(){
	cout << "==== MARKET ====" << endl;
	printWeapons();
	printArmors();
	printSpells();
}

void market::printItems(int type){
	for(int i = 0; i < items[type].size(); i++){
		cout << i + 1 << ")" << endl;
		items[type][i]->print();
	}
}

void market::printWeapons(){
	cout << "==== WEAPONS ====" << endl;
	printItems(weapon);
}


void market::printArmors(){
	cout << "==== ARMORS ====" << endl;
	printItems(armor);
}


void market::printPotions(){
	cout << "======= POTIONS =======" << endl;
	printItems(potion);
}


void market::printSpell(int type){
	for(int i = 0; i < spells[type].size(); i++){
		cout << i + 1 << ")" << endl;
		spells[type][i]->print();
	}
}


void market::printSpells(){
	cout << "==== SPELLS ====" << endl;
	cout << "==== ICE SPELLS ====" << endl;
	printSpell(ice);
	cout << "==== FIRE SPELLS ====" << endl;
	printSpell(fire);
	cout << "==== LIGHTING SPELLS ====" << endl;
	printSpell(lighting);
}


void market::buy_spell(int type){
	int spellOption;
	for(int i = 0; i < spells[type].size(); i++){
			cout << i + 1 << ")" << endl;
			Spell* sp = spells[type][i];
			sp->print();
	}
	cout << "Choose the spell you want to buy range from 1 to " << spells[type].size() << " or 0 to cancel" << endl;
	cin >> spellOption;
	if(spellOption > 0 && spellOption <= spells[type].size()){
		if(this->hs->buySpell(spells[type][spellOption - 1], type)){
		 	spells[type].erase(spells[type].begin() + spellOption - 1);
		}
	}
}


void market::buy_spell(){
	printSpells();
	cout << "What spell would you like to buy?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
	int spellType = 4;
	while(spellType > 3 || spellType < 0){
		cin >> spellType ;
		cout << "What spell would you like to buy?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
	}
	int spellOption;
	if(spellType == 1 && spells[ice].size() != 0){
		buy_spell(ice);
	}
	else if(spellType == 2 && spells[fire].size() != 0){
		buy_spell(fire);
	}
	else if(spells[lighting].size() != 0){
		buy_spell(lighting);
	}
}


void market::buy_item(int type){
	printItems(type);
	cout << "What armor would you like to buy?(type from range 1 to " << items[type].size() << " or 0 to cancel your action" << endl;
	int option;
	cin >> option;
	if(option > 0){
		if(hs->buy(items[type][option - 1], type)){
			items[type].erase(items[type].begin() + option - 1);
		}
	}
}


void market::buy(){
	int buyOption = 5;
	cout << "Would you like to buy a weapon(1), an armor(2), a spell(3), a potion(4) : " << endl;
	while(buyOption > 4){
		cin >> buyOption;
		cout << "Would you like to buy a weapon(1), an armor(2), a spell(3) : " << endl;
	}
	if(buyOption == 1 && items[weapon].size() != 0){
		buy_item(weapon);
	}else if(buyOption == 2 && items[armor].size() != 0){
		buy_item(armor);
	}else if(buyOption == 3){
		buy_spell();
	}else if(buyOption == 4 && items[potion].size() != 0){
		buy_item(potion);
	}		
}


void market::sellItem(int type){
	hs->print_items(type);
	cout << "Which Item would you like to sell?" << endl;
	int toSell;
	cin >> toSell;
	Item* item_to_sell = hs->sellItem(toSell, type);
	if(item_to_sell != NULL)	items[type].push_back(item_to_sell);
}


void market::sellSpell(int type){
	hs->print_spells(type);
	cout << "Which Spell would you like to sell?" << endl;
	int toSell;
	cin >> toSell;
	Spell* sp = hs->sellSpell(toSell, type);
	if(sp != NULL)	spells[type].push_back(sp);	
}


void market::sell(){
	cout << "What would you like to sell: (1)Weapons (2)Armors (3)Potions (4)Ice Spells (5)Fire Spells (6)Lighting Spells [Press 0 or something else than the options to cancel]" << endl;
	int sellOption;
	cin >> sellOption;
	if(sellOption == 1){
		sellItem(weapon);
	}else if(sellOption == 2){
		sellItem(armor);
	}else if(sellOption == 3){
		sellItem(potion);		
	}else if(sellOption == 4){
		sellSpell(ice);		
	}else if(sellOption == 5){
		sellSpell(fire);
	}else if(sellOption == 6){
		sellSpell(lighting);		
	}
}


void market::interact(){
	cout << "Welcome to the store!" << endl;
	cout << "Would you like to buy something?(1 = yes / 0 = no)" << endl;
	bool i_want_to_buy_sell;
	cin >> i_want_to_buy_sell;
	while(i_want_to_buy_sell){
		cout << "Your money: " << hs->getMoney() << endl;
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
	for(int i = 0; i < 3; i++)
        for(int j = 0; j < items[i].size(); j++)
            delete items[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < spells[i].size(); j++)
            delete spells[i][j];									
}
