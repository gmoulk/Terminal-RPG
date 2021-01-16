#include <iostream>
#include "Items_and_spells.h"
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
		vector<Spell*> spells;
		vector<Potion*> potions;
	public:
		market(){
			srand((unsigned) time(NULL));
			int num_of_weapons = rand() % max_weapons;
			int num_of_armors = rand() % max_armors;
			int num_of_spells = rand() % max_spells;
			cout << "[DEBUG NUM] " << num_of_weapons;
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
								cout << "[DEBUG] NAME " << name << endl;
							}
							else if(j == 4){
								level = atoi(token1);
								cout << "[DEBUG] LEVEL " << level << endl;
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
								cout << "[DEBUG] NAME " << name << endl;
							}
							else if(j == 4){
								name = string(token1);
								cout << "[DEBUG] LEVEL " << level << endl;
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
					  	spells.push_back(sp);
					  }
					if(class_ == "IceSpell"){
						IceSpell* sp = new IceSpell(level,mana,name,stat,price,damageM,damageL);
						spells.push_back(sp);
					}
					if(class_ == "LightingSpell"){
						LightingSpell* sp = new LightingSpell(level,mana,name,stat,price,damageM,damageL);
						spells.push_back(sp);
					}						
  					in.close();				
			}
		}
		
		void print(){
			cout << "==== MARKET ====" << endl;
			cout << "==== WEAPONS ====" << endl;
			int j = 1;
			for(int i = 0; i < weapons.size(); i++){
				cout << j + 1 << ")" << endl;
				Weapon* wp = weapons[i];
				wp->print();
				j++;
			}
			cout << "==== ARMOR ====" << endl;
			for(int i = 0; i < armors.size(); i++){
				cout << j + 1 << ")" << endl;
				Armor* ar = armors[i];
				ar->print();
				j++;
			}
			cout << "==== SPELLS ====" << endl;
			for(int i = 0; i < spells.size(); i++){
				cout << j + 1 << ")" << endl;
				Spell* sp = spells[i];
				sp->print();
				j++;
			}
			int item_i_want_to_buy;
			cin >> item_i_want_to_buy;
			if(item_i_want_to_buy < weapons.size()){
				
			}
			
		}
		
		void interact(){
			cout << "Welcome to the store!" << endl;
			cout << "Would you like to buy something?(1 = yes / 0 = no)" << endl;
			bool i_want_to_buy;
			cin >> i_want_to_buy;
			while(i_want_to_buy){
				cout << "Choose one of the following(by typing the id of the item) to buy or type 0 to cancel" << endl;
				this->print();
				cout << "Would you like to buy something?(1 = yes / 0 = no)" << endl;
				cin >> i_want_to_buy;
			}
		}
};
