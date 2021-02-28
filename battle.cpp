#include "battle.h"

void Battle::heroes_take_action(){
    int monster_index, action;
    // input
    cout << "===== HERO TURN ====" << endl;
    for(int i = 0; i < this->heroes->number_of_heroes; i++){
        cout << this->heroes->heroes[i]->getName() << " turn" << endl;
        cout << "What would you want to do?1)Normal attack 2)Spell Attack 3)Consume potion)" << endl;
        cin >> action;

        if(action == 1){
            // option 1: attack with weapon
            int attack = this->heroes->attack(i);
            cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << endl;
            int monster_index;
            cin >> monster_index;
            this->monsters->getAttacked(monster_index - 1, attack);
        
        }else if(action == 2){	
            // option 2: attack with spell
            cout << "Select the type of spell you want to use (1)Ice Spell (2)Fire Spell (3)Lighting Spell" << endl;
            int spellType = 4;
            while(spellType > 3 || spellType < 0){
                cin >> spellType ;
                cout << "What spell would you like to use?(1)Ice Spell (2) Fire Spell (3) Lighting Spell" << endl;
            }
            Spell* sp;
            if(spellType == 1){
                sp = this->heroes->useIceSpells();
            }else if(spellType == 2){
                sp = this->heroes->useFireSpells();
            }else{
                sp = this->heroes->useLightSpells();
            }
            if(sp != NULL){
                    cout << "Select a monster a monster for your attack:(Number from 1 to " << this->monsters->get_monsters_num() << ")" << endl;
                    int monster_index;
                    cin >> monster_index;
                    this->monsters->getAttacked(monster_index - 1, heroes->attack(i,sp));
                    this->monsters->getInfected(monster_index - 1, sp);
            }
        }
        else if(action == 3 && heroes->items[potion].size() != 0){
            this->heroes->printPotions();
            cout << "Select one of the above potions range 1 to " << this->heroes->items[potion].size() << " or type 0 to cancel." << endl;
            int option;
            cin >> option;
            if(	option > 0 && option <= this->heroes->items[potion].size() 
                && this->heroes->heroes[i]->use_potion((Potion*)(heroes->items[potion][option - 1])))
                heroes->items[potion].erase(heroes->items[potion].begin() + option - 1);
        }
    }
}

void Battle::displayStats() const{
    cout << "======== HEROES =============" << endl;
    for(int i = 0; i < this->heroes->number_of_heroes; i++)
        if(!this->heroes->heroes[i]->isFaint())
            this->heroes->heroes[i]->print();	
    cout << "======== MONSTERS =============" << endl;
    for(int i = 0; i < this->monsters->number_of_monsters; i++)
        if(!this->monsters->monsters[i]->isFaint())
            this->monsters->monsters[i]->print();
}

bool Battle::battle(){  // the main function of the battle, everyhting happens in here
    //battle loop
    for(int round = 1; (!heroes_are_dead() && !monsters_are_dead()); round++){
        std::cout << "ROUND: " << round << std::endl;
        cout << "Would you like to print the stats of the battle participants?(1 = Yes/ 0 = No)" << endl;
        bool printStats;
        cin >> printStats;
        if(printStats){
            this->displayStats();
        }	
        heroes->change_armor();
        heroes->change_weapon();
        heroes_take_action();	// attack with spell, attack with weapon, use potion

        // pc's turn
        for (int i = 0; i < monsters->get_monsters_num(); i++){
            if (monsters->monsters[i]->getcurrentHealth() != 0){
                this->heroes->getAttacked(monsters->monsters[i]->attack());
            }
        }
        this->heroes->update();
        this->monsters->update();
    }
    for(int i = 0; i < heroes->get_heroes_num(); i++)
        heroes->heroes[i]->revive();
    // end of battle
    return monsters_are_dead(); 
}