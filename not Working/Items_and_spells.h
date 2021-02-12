#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;


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
    virtual void print() = 0;
    virtual int itemClass() = 0;
    double getPrice() const{
		return this->price;
	}
	string getName() const{
		return this->name;
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
    	cout << "[DEBUG] Weapon created with name " << name << " level " << level << " price " << price << " damage " << dmg << endl;  
    }
    
    double weapon_damage(){
        return damage;
    }
    
    void print(){
    	cout << "=======  WEAPON  =======" << endl;
    	cout << " Name: "<< this->name << endl;
		cout << " Price: " << this->price << endl;
		cout << " Attack Points: " << this->damage << endl;
		cout << " Number Of Hands Needed: " << this->is_two_handed + 1 << endl;
		cout << " Info: Weapon that increases "<< endl;
		cout << "       your attack points    "<< endl;
		cout << "========================" << endl;
	}
	
	int numOfHands(){
		return this->is_two_handed + 1;
	}
	
	int itemClass(){
		return 1;
	}
};


class Armor:public  Item{

private:
    double dmg_red_percentage;
    
public:
    Armor(int level, double price_to_pay, std::string name, double dmg)
    :Item(level, price_to_pay, name), dmg_red_percentage(dmg){
    }
    
    double get_damage_percentage() const{
        return dmg_red_percentage;
    }
    
    void print(){
    	cout << "=======  ARMOR  =======" << endl;
    	cout << " Name: "<< this->name << endl;
		cout << " Price: " << this->price << endl;
		cout << " Damage percentage absorbed: " << this->dmg_red_percentage << endl;
		cout << " Info: Armor that arbsorbs "<< endl;
		cout << "        enemy attack points "<< endl;
		cout << "========================" << endl;
	}
	
	int itemClass(){
		return 2;
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
    
    void print(){
    	cout << "=======  POTION  =======" << endl;
    	cout << " Name: "<< this->name << endl;
		cout << " Price: " << this->price << endl;
		cout << " Statistic increase percentage: " << this->stat_increase_percentage << endl;
		cout << " Info: Potion that increases one of "<< endl;
		cout << "        your stats "<< endl;
		cout << "========================" << endl;
	}
	
	int itemClass(){
		return 3;
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
	double price;
	int rounds;
public:
    Spell(int level, int  mana, std::string name, double price, int max_damage, int least_damage)
    :level_needed_to_use(level), mana_to_consume(mana), name(name), price(price) , max_damage(max_damage), least_damage(least_damage){
       /*  std::cout << "A Spell has been created\n"; */
    }
    int get_mana() const{
        return mana_to_consume;
    }
    // will be implemented later
    // actual type to return is not determined yet
    double damage_to_do(int dexterity){
		srand((unsigned) time(NULL));
		int rand_num = rand() % dexterity;
		return rand_num % max_damage + least_damage;
	}  // dexterity could be double but int is preffered
	
	void print() const{
    	cout << " Name: "<< this->name << endl;
		cout << " Price: " << this->price << endl;
		cout << " Mana: " << this->mana_to_consume << endl;
		cout << " Max Damage: " << this->max_damage << endl;
		cout << " Least Damage: " << this->least_damage << endl;
		cout << "========================" << endl;
	}
	
	double getPrice() const{
		return this->price;
	}
	
	virtual int getRed() = 0;
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
	void print(){
		cout << "======== ICE SPELL ========" << endl;
		Spell::print();
	}
    IceSpell(int level, int  mana, std::string name, double percentage , double price , int max_damage, int least_damage)
    :Spell(level, mana, name , price, max_damage, least_damage), dmg_reduction_percentage(percentage){ }
	int getRed(){
		return dmg_reduction_percentage;
	}
};


class FireSpell:public Spell{
private:
    double enemy_defence_red_perc;
public:
	void print(){
		cout << "======== FIRE SPELL ========" << endl;
		Spell::print();
	}
    FireSpell(int level, int  mana, std::string name, double percentage, double price , int max_damage, int least_damage)
    :Spell(level, mana, name, price , max_damage , least_damage), enemy_defence_red_perc(percentage){}
    int getRed(){
		return enemy_defence_red_perc;
	}
};


class LightingSpell:public Spell{
private:
    double enemy_dodge_red_perc;
public:
	void print(){
		cout << "======== LIGHTING SPELL ========" << endl;
		Spell::print();
	}
    LightingSpell(int level, int  mana, std::string name, double percentage, double price, int max_damage, int least_damage)
    :Spell(level, mana, name, price, max_damage, least_damage), enemy_dodge_red_perc(percentage){}
    int getRed(){
		return enemy_dodge_red_perc;
	}
};

class Effect{

protected:
    int rounds_left;
    double percentage_reduction;
public:
    Effect(int rounds=3, double percentage=0.33)
    :rounds_left(rounds), percentage_reduction(percentage){}

    virtual bool update() = 0;
    virtual void apply_effect() = 0;
};


class Fire_Effect: public Effect{

protected:
    int& value_to_reduce;
    int initial_value;
    
public:
    Fire_Effect(int& to_reduce, int rounds=3, double percentage=0.33)
    :value_to_reduce(to_reduce),initial_value(to_reduce), Effect(rounds, percentage){}

    void apply_effect(){
    	cout << "DEBUG 1 " << percentage_reduction << endl;
    	cout << "DEBUG 1.5 "<< value_to_reduce << endl;
    	cout << "DEBUG 2 " << percentage_reduction*value_to_reduce << endl;
        value_to_reduce = value_to_reduce - percentage_reduction*value_to_reduce;
        cout << "DEBUG " << value_to_reduce << endl;
    }

    bool update(){
        if (rounds_left == 0){
            value_to_reduce = initial_value;
            return false;   // monster.effect = null
        }
        rounds_left--;
        return true;
    }
};


class Ice_Effect:public Fire_Effect{
public:
    Ice_Effect(int& to_reduce, int rounds=3, double percentage=0.33)
    :Fire_Effect( to_reduce,  rounds=3,  percentage=0.33){}
    
    bool update(){
        if (rounds_left == 0){
            value_to_reduce = initial_value;
            return false;   // monster.effect = null
        }
        rounds_left--;
        return true;
    }
};


class Lighting_effect: public Effect{

private:
    double& value_to_reduce;
    double& initial_value;
    
public:
    Lighting_effect(double& to_reduce, int rounds=3, double percentage=0.33)
    :value_to_reduce(to_reduce),initial_value(to_reduce),  Effect(rounds, percentage){}

    void apply_effect(){
        value_to_reduce -= percentage_reduction*value_to_reduce;
    }

    bool update(){
        if (rounds_left == 0){
            value_to_reduce = initial_value;
            return false;   // monster.effect = null
        }
        rounds_left--;
        return true;
    }
};

