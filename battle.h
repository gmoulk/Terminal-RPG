#pragma once
#include "Living.h"
#include <string>


// Maybe some implmentations will change
// for the easiest implementaiton of battle
class heroe_squad{

private:
	int number_of_heroes;
	Hero* heroes[3];

public:
	heroe_squad(Hero* hero1, Hero* hero2=NULL, Hero* hero3=NULL, int _number_of_heroes = 1)
	:number_of_heroes(_number_of_heroes){
		heroes[0] = hero1;
		heroes[1] = hero2;
		heroes[2] = hero3;
	}
	int get_heroes_num() const{
		return number_of_heroes;
	}
    void print() const{
        for (int i=0; i < number_of_heroes; i++)
            heroes[i]->print();
    }
};



// maximum number of monsters not determined yet
class monsters_squad{
    // maximum number of monsters is not known yet, pretend is 6
private:
    int number_of_monsters;
    Monster* monsters[6];

public:
    monsters_squad(Monster* _monsters[6], int monsters_num)
	:number_of_monsters(monsters_num){
        for (int i=0; i < number_of_monsters; i++){
            monsters[i]  = _monsters[i];
        }
    }

    int get_monsters_num() const{
		return number_of_monsters;
	}
    void print() const{
        for (int i=0; i < number_of_monsters; i++)
            monsters[i]->print();
    }

};

class battle{
// battle takes place on a square on the grid(grid not made yet)
private:
    heroe_squad* heroes;
    monsters_squad* monsters;
public:
    battle(heroe_squad* heroes,  monsters_squad* monsters)
    :heroes(heroes), monsters(monsters) {
        std::cout << "A battle is about to start!" << std::endl;
    }
    // attacks will be implemented later
    // 
};