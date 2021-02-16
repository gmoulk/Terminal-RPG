#include <iostream>
#include "battle.h"
#include "market.h"
#include "grid.h"
using namespace std;

class game{
	private:
		heroe_squad* hs;
		commonSquare* cs;
		marketSquare* mrk;
		int x;
		int y;
		int access[10][10];
	public:
		void displayMap(int x, int y,int access[10][10]){
			cout << "=========== MAP ============" << endl;
			for(int i = 0; i < 10; i++){
				for(int j = 0; j < 10; j++){	
					cout << "[";
					if(x == i && y == j)
						cout << "T";
					if(access[i][j] == -1)
						cout << "NA]";
					if(access[i][j] == 0)
						cout << " ]";
					if(access[i][j] == 1)
						cout << "M]";	
				}
				cout << endl;
			}
		}

		void create_terrain(){
			srand((unsigned) time(NULL));
			for(int i = 0; i < 10; i++){
				for(int j = 0; j < 10; j++){
					double randNum = ( (double)rand() / RAND_MAX);
					if(randNum < 0.65)
						access[i][j] = 0;	// common square(dont know if there are monsters)
					else if(randNum < 0.9)
						access[i][j] = 1;	// market
					else 
						access[i][j] = -1;	// not accesible
				}
			}
			
			for(int i = 0; i < 10; i++)
				for(int j = 0; j < 10; j++)
					if(access[i][j] == 0 || access[i][j] == 1){
						this->x = i;
						this->y = j;
					}
		}
		

		void create_tarrain_debug(){
			

		}


		void move(){
			while(1){
				cout << "Where would you like to move (1) North (2) West (3) East (4) South (if you want to cancel just press 0)" << endl;	
				int option;
				cin >> option;
				while(option > 4)
					cin >> option;
				if(option == 0)
					return;	
				else if(option == 1){
					this->y--;
					if(y < 0)
						this->y = 9;
					if(this->access[x][y] != -1)
						return;	
					cout << "This move is invalid this area is Not Accessible!" << endl;		
					this->y++;
					if(this->y == 10)
						this->y = 0;
				}
				else if(option == 2){
					this->x--;
					if(x < 0)
						this->x = 9;
					if(this->access[x][y] != -1)
						return;	
					cout << "This move is invalid this area is Not Accessible!" << endl;		
					this->x++;
					if(this->x == 10)
						this->x = 0;
				}
				else if(option == 3){
					this->x++;
					if(x > 9)
						this->x = 0;
					if(this->access[x][y] != -1)
						return;	
					cout << "This move is invalid this area is Not Accessible!" << endl;		
					this->x--;
					if(this->x == -1)
						this->x = 9;
				}
				else if(option == 4){
					this->y++;
					if(y > 9)
						this->y = 0;
					if(this->access[x][y] != -1)
						return;	
					cout << "This move is invalid this area is Not Accessible!" << endl;		
					this->y--;
					if(this->y == -1)
						this->y = 9;
				}			
			}
		}

		
		
		game(){
			this->cs = NULL;    
			this->mrk = NULL;
			cout << "Select number of characters in your team:(from 1 to 3): ";	
			Hero* team[3];
			for(int i = 0; i < 3; i++)
				team[i] = NULL;
			int numberOfCharacters = 10;
			while(numberOfCharacters > 3 || numberOfCharacters <= 0)
				cin >> numberOfCharacters;	
			int option;
			for(int i = 0; i < numberOfCharacters; i++){
				cout << "Give the name of your hero: ";
				getchar();
				string name;
				getline(cin,name);
				cout << "Select the class of your hero(1.Warrior 2.Sorcerer 3.Paladin):" << endl;
				cin >> option;
				bool legalOption = 0;
				while(!legalOption)
					switch(option){
						case 1:
							team[i] = new Warrior(name);
							legalOption = 1;
							break;
						case 2:
							team[i] = new Sorcerer(name);
							legalOption = 1;
							break;
						case 3:
							team[i] = new Paladin(name);
							legalOption = 1;		
							break;
						default:
							cout << "Your number must be in range 1 to 3" << endl;	
					}
				}
				this->hs = new heroe_squad(team[0],team[1],team[2],numberOfCharacters);
				
				
				create_terrain();
				
				// GAME LOOP
				bool quit = false;
				cout << "Welcome to Terminal RPG" << endl;
				while(!quit){
					if(access[x][y] == 0 && this->cs == NULL){
						this->cs = new commonSquare(this->hs);
						delete this->cs;
						this->cs = NULL;						
					}
					if(access[x][y] == 1 && this->mrk == NULL){
						this->mrk = new marketSquare(this->hs);
					}
						
					cout << "==============================" << endl;
					cout << "Would you like to (1)Quit Game (2)Show Map (3)Check Inventoty (4)Change Armor (5)Change Weapon (6)Show Heroes ";
					if(this->mrk != NULL)
						cout << "(7) See the market one more time ";
					cout << " (8) Move" << endl;	
					int option;
					cin >> option;				
					if(option == 2)
						displayMap(x,y,access);
					else if(option == 3)
						hs->checkInvetory();
					else  if(option == 4)
						hs->change_armor();
					else if(option == 5)
						hs->change_weapon();
					else if(option == 6)
						hs->print();
					else if(option == 7 && this->mrk != NULL)
						this->mrk->interact();
					else if(option == 8)
						this->move();	
					else
						quit = true;
					if(this->mrk != NULL){
						delete this->mrk;
						this->mrk = NULL;
					}
				}		
		}	
};
