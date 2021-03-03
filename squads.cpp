#include "battle.h"

Spell* heroe_squad::useSpells(int type){
    if(this->spells[type].size() == 0){
		std::cout << "No Spells available" << endl;
		return NULL;
	}
    for(int i = 0; i < spells[type].size(); i++){
	    std::cout << i + 1 << ")" << endl;
		Spell* sp = spells[type][i];
		sp->print();
		i++;
	}
	std::cout << "Choose the spell you want to use range from 1 to " << spells[type].size() << " or 0 to cancel" << endl;
	int spellOption;
	std::cin >> spellOption;
	if(spellOption > 0 && spellOption <= spells[type].size()){
		return spells[type][spellOption - 1];
	}
	return NULL;
}

void heroe_squad::change_armor(int hero_index, int option){
    if(items[armor].size() < option)	return;
    items[armor][option - 1] = (Armor*) heroes[hero_index - 1]->equip((Armor*)(items[armor][option - 1]));
    if(items[armor][option - 1] == NULL){
        items[armor].erase(items[armor].begin() + option - 1);
    }
}
	
void heroe_squad::change_weapon(int hero_index, int option){
    if(items[weapon].size() < option)	return;
    Weapon* w1 = (Weapon*)(items[weapon].at(option - 1));
    w1->print();
    Weapon** weaps = (Weapon**) heroes[hero_index]->equip(w1);
    items[weapon][option - 1] = weaps[0];
    if(items[weapon][option - 1] == NULL)
    items[weapon].erase(items[weapon].begin() + option - 1);
    if(weaps[1] != NULL)
    items[weapon].push_back(weaps[1]);
    delete[] weaps;	
}

void heroe_squad::getAttacked(int attackPoints){
    for(int i = 0; i < 3; i++){
        if(!this->heroes[i]->isFaint()){
            this->heroes[i]->getAttacked(attackPoints);
            cout << " " << this->heroes[i]->getName() << endl;
            return;
        }
    }
}

void heroe_squad::checkInvetory(){
    cout << "======= ARMORS ======" << endl;
    this->printArmors();
    cout << "======= WEAPONS ======" << endl;
    this->printWeapons();
    cout << "======= Potions =======" << endl;
    this->printPotions();
    cout << "======= ICE SPELLS =======" << endl;
    this->printIceSpells();
    cout << "======= FIRE SPELLS =======" << endl;
    this->printFireSpells();
    cout << "======= LIGHTING SPELLS =======" << endl;
    this->printLightingSpells();	
}

bool heroe_squad::buy(Item* item, int type){
    if (item->getPrice() <= this->money){
        this->money -= item->getPrice();
        this->items[type].push_back(item);
        return 1;
    }
    return 0;
}

Item* heroe_squad::sellItem(int i, int type){
    if(i <= 0 || i > this->items[type].size())
        return NULL;
    Item* toReturn = this->items[type][i - 1];
    this->items[type].erase(items[type].begin() + i - 1);
    this->money += toReturn->getPrice()/2;
    return toReturn;	
}

Spell* heroe_squad::sellSpell(int i, int type){
    if(i <= 0 || i > this->spells[type].size())
        return NULL;
    Spell* toReturn = this->spells[type][i - 1];
    this->spells[type].erase(spells[type].begin() + i - 1);
    this->money += toReturn->getPrice()/2;
    return toReturn;
}

int heroe_squad::averageLevel(){
    int avgLvl = 0;
    for(int i = 0; i < 3; i++){
        if(this->heroes[i] != NULL)
            avgLvl += this->heroes[i]->getLevel();	
    }
    avgLvl = avgLvl / 3;
    return avgLvl;
}

void heroe_squad::battleWon(int numOfMonsters){
    cout << "Battle Won!" << endl;	
    if(this->averageLevel() < 1){}
        this->money += 0.1*this->money*numOfMonsters;
    if(this->averageLevel() < 3)
        this->money += 0.2*this->money*numOfMonsters;	
    else
        this->money += 0.3*this->money*numOfMonsters;
    for(int i = 0; i < numOfMonsters; i++)
        this->heroes[i]->getExperience(numOfMonsters);
}

void heroe_squad::change_armor(){
    // input
    bool want_to_change = false;    
    std::cout << "do you want to change a hero's armor?(1 = yes / 0 = no)" << std::endl;
    std::cin >> want_to_change;
    
    while(want_to_change){
        // validate if there is any armor
        cout << "Would you like to take out your armor?(1 = Yes/ 0 = No)" << endl;
        bool takeOut;
        cin >> takeOut;
        if(takeOut){
            std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
            int hero_index;
            cin >> hero_index;
            Armor* arm = this->heroes[hero_index - 1]->takeOutArmor();
            if(arm != NULL)
                this->items[armor].push_back(arm);
        }
        if (items[armor].size() == 0){
            std::cout << "You have no armor in your inventory" << std::endl;
            return;
        }
        // input
        int hero_index;
        std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
        std::cin >> hero_index;
        std::cout << "Select the armor you want to equip: " << endl;
        std::cout << "ARMOR LIST:\n--------------------"<<std::endl;
        // print armor list
        for(int i = 0; i < this->items[armor].size(); i++){
            Armor* arm = (Armor*)(this->items[armor].at(i));
            cout << i + 1 << ")";
            arm->print();
        }
        std::cout << "             \n--------------------"<<std::endl;
        // input
        int option;
        cin >> option;
        this->change_armor(hero_index, option);
        cout << "Would you want to change something else?" << endl;
        cin >> want_to_change;
    }
}

void heroe_squad::change_weapon(){
    bool want_to_change;
    std::cout << "Do you want to change a hero's weapon?(1 = yes / 0 = no)" << std::endl;
    std::cin >> want_to_change;

    while(want_to_change){
        cout << "Would you like to take out your weapons?(1 = Yes/ 0 = No)" << endl;
        bool takeOut;
        cin >> takeOut;
        if(takeOut){
            std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
            int hero_index;
            cin >> hero_index;
            Weapon** wps = this->heroes[hero_index - 1]->takeOutWeapons();
            if(wps[0] != NULL)
                this->items[weapon].push_back(wps[0]);
            if(wps[1] != NULL)
                this->items[weapon].push_back(wps[1]);
            delete[] wps;	
        }
        if (items[weapon].size() == 0){
            std::cout << "You have no weapon in your inventory" << std::endl;
            return;
        }
        //input
        int hero_index;
        std::cout << "Pick a hero(" << 1 << "-" << this->get_heroes_num() << ")" << std::endl;
        std::cin >> hero_index;
        std::cout << "Select the weapon you want to equip: " << endl;
        // print weapons
        std::cout << "WEAPONS LIST:\n--------------------"<<std::endl;
        for(int i = 0; i < this->items[weapon].size(); i++){
            Weapon* wep = (Weapon*)(this->items[weapon].at(i));
            cout << i + 1 << ")";
            wep->print();
        }
        std::cout << "             \n--------------------"<<std::endl;
        // input
        int option;
        cin >> option;
        this->change_weapon(hero_index-1, option);
        cout << "Would you want to change something else?" << endl;
        cin >> want_to_change;
    }
}


void heroe_squad::usePotion(int hero_index){
    if(this->items[potion].size() == 0){
        cout << "No potions in inventory!" << endl;
        return;
    }
    this->printPotions();
    cout << "Select one of the above potions range 1 to " << this->items[2].size() << " or type 0 to cancel." << endl;
    int option;
    cin >> option;
    if(option > 0 && option <= this->items[2].size() && this->heroes[hero_index - 1]->use_potion((Potion*) this->items[2].at(option - 1)) )
        items[2].erase(items[2].begin() + option - 1);
}

void monsters_squad::getInfected(int index,Spell* sp){
    // check type
    if (dynamic_cast<FireSpell*>(sp)){
        this->monsters[index]->getInfected((FireSpell *)sp);
    }else if (dynamic_cast<IceSpell*>(sp)){
        this->monsters[index]->getInfected((IceSpell *)sp);
    }else{
        this->monsters[index]->getInfected((LightingSpell *)sp);
    }
}


heroe_squad::~heroe_squad(){
    for(int i = 0; i < this->number_of_heroes; i++)
        delete this->heroes[i];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < items[i].size(); j++)
            delete items[i][j];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < spells[i].size(); j++)
            delete spells[i][j];       						
}	    