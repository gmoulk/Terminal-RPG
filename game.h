#include "battle.h"
#include "market.h"
#include "grid.h"

class game{
	private:
		heroe_squad* hs;
		commonSquare* cs;
		marketSquare* mrk;
		int x;
		int y;
		int access[10][10];
	public:
		void displayMap(int x, int y,int access[10][10]);

		void create_terrain();
		
		void move();
			
		game();
		
		~game(){
			delete this->hs;
		}	
};
