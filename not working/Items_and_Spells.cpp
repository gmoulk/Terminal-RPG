#include <iostream>
#include <string>


// BASE CLASSES ARE NOT ABSTRACT YET
// INFORMATION IS NEED TO IMPLEMENT SOME FUNCION THAT ARE MISSING OR ARE NOT IMPLEMENTED YET



// Item is not pure virtual yet
class Item{

protected:
    const int level_needed_to_use;
    const double price;
    const std::string name;
public:
    Item(int level, double price_to_pay, std::string name)
    :level_needed_to_use(level), price(price_to_pay), name(name){
        /* std::cout << "An item has been created\n"; */
    }
    // maybe virtual destructor
};

/*  weapon  double handed or not, standard damage
    armor   reduces damage taken 
    potion  increases a stat
*/

class Weapon:public  Item{

private:
    double damage;   
    bool is_two_handed;

public:
    Weapon(int level, double price_to_pay, std::string name, double dmg, bool two_handed)
    :Item(level, price_to_pay, name), damage(dmg), is_two_handed(two_handed){
    }
    double weapon_damage(){
        return damage;
    }
};


class Armor:public  Item{

private:
    double dmg_red_percentage;
    
public:
    Armor(int level, double price_to_pay, std::string name, int dmg)
    :Item(level, price_to_pay, name), dmg_red_percentage(dmg){
    }
    double get_damage_percentage() const{
        return dmg_red_percentage;
    }
};


class Potion:public  Item{

private:
    double stat_increase_percentage;
    
public:
    Potion(int level, double price_to_pay, std::string name, int increase_percentage)
    :Item(level, price_to_pay, name), stat_increase_percentage(increase_percentage){
    }
    double get_increase_percentage() const{
        return stat_increase_percentage;
    }
};



/* SPELSS:*/

// Spell is not pure virtual yet

class Spell{

protected:
    const int level_needed_to_use;
    const int mana_to_consume;
    const std::string name;
    int least_damage;
    int max_damage;

public:
    Spell(int level, int  mana, std::string name, int max_damage, int least_damage)
    :level_needed_to_use(level), mana_to_consume(mana), name(name) , max_damage(max_damage), least_damage(least_damage){
       /*  std::cout << "A Spell has been created\n"; */
    }
    int get_mana() const{
        return mana_to_consume;
    }
    // will be implemented later
    // actual type to return is not determined yet
    double damage_to_do(int dexterity){}  // dexterity could be double but int is preffered
};

/* one extra effect that lasts for a number of rounds
and reduces 
               (1)damage taken             --> apply effect on hero
               (2)enemy defense            --> apply effect on enemy
               (3)chance of enemy dodging  --> apply effect on enemy
    1.IceSpell
    2.FireSpell
    3.LightingSpell 
*/

class IceSpell:public Spell{

private:
    double dmg_reduction_percentage;
public:
    IceSpell(int level, int  mana, std::string name, double percentage)
    :Spell(level, mana, name), dmg_reduction_percentage(percentage){ }

};


class FireSpell:public Spell{
private:
    double enemy_defence_red_perc;
public:
    FireSpell(int level, int  mana, std::string name, double percentage)
    :Spell(level, mana, name), enemy_defence_red_perc(percentage){}
};


class LightingSpell:public Spell{
private:
    double enemy_dodge_red_perc;
public:
    LightingSpell(int level, int  mana, std::string name, double percentage)
    :Spell(level, mana, name), enemy_dodge_red_perc(percentage){}
};
