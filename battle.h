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
    friend class Battle;
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
    friend class Battle;
};


class Battle{
// battle takes place on a square on the grid(grid not made yet)
private:
    heroe_squad* heroes;
    monsters_squad* monsters;
    bool heroes_are_dead(){
        for(int i = 0; i < heroes->get_heroes_num(); i++){
            if (heroes->heroes[i]->getcurrentHealth() != 0){
                return false;
            }
        }
        return true;
    }
    bool monsters_are_dead(){
        for(int i = 0; i < monsters->get_monsters_num(); i++){
            if (monsters->monsters[i]->getHealth() != 0){
                return false;
            }
        }
        return true;
    }
    bool monsters_are_dead;

public:

    Battle(heroe_squad* heroes,  monsters_squad* monsters)
    :heroes(heroes), monsters(monsters) {
        std::cout << "A battle is about to start!" << std::endl;
    }

    // actual battle
    bool battle(){  // the main function of the battle, everyhting happens in here
        int round = 1;
        //battle loop
        for(round = 1; (!heroes_are_dead() && !monsters_are_dead()); round++){
            //
            std::cout << "ROUND: " << round << std::endl;
            // player's round
            // ARMOR AND WEAPON CHANGE
            bool want_to_change = false;    
            // armor change(does not count for an action)
            std::cout << "do you want to change a hero's armor?" << std::endl;
            std::cin >> want_to_change;
            while(want_to_change){
                int hero_index;
                std::cout << "Pick a hero(" << 1 << "-" << heroes->get_heroes_num() << ")" << std::endl;
                std::cin >> hero_index;
                // number evalutaion will be implemented later
                // armor change will be implemented later
            
            // weapon change(does not count for an action)
            std::cout << "do you want to change a hero's weapon?" << std::endl;
            std::cin >> want_to_change;
             while(want_to_change){
                int hero_index;
                std::cout << "Pick a hero(" << 1 << "-" << heroes->get_heroes_num() << ")" << std::endl;
                std::cin >> hero_index;
                // number evalutaion will be implemented later
                // weapon change will be implemented later
            }
            // ask user to pick a hero who has not attacked  and not used any potion to do something
            // option 1: attack with weapon
            // option 2: attack with spell
            // option 3: drink a potion

            // pc's round(AI KAPAA KEEPO)
            for (int i = 0; i < monsters->get_monsters_num(); i++){

                if (monsters->monsters[i]->getHealth() != 0){
                    // every monster does something if its not dead
                    // i will figure out later what
                }
            }
        }
        // end of battle
        return monsters_are_dead(); 
        }

    }
};
