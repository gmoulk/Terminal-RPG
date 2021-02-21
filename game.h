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

		void displayMap(int x, int y);

		void make_heroes();
		
		void create_terrain();
		
		void move();

	public:
		
		game();
		
		~game(){
			delete this->hs;
		}	
};