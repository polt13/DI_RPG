#ifndef RPG_H
#define RPG_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Hero;
class Monster;
enum class cstats { DEX,
    STR,
    AGIL,
    HP,
    MP };

enum class spellType {
    ICE,
    FIRE,
    LIGHTNING
};

class Item {
public:
    virtual void print() const = 0;

protected:
    const std::string name;
    const int buy_price;
    const int min_level;

public:
    Item(const std::string&, const int, const int);
    int getPrice() const;
};

class Weapon : public Item {
    const int dmg;
    const bool two_handed;

public:
    void print() const;
    Weapon(const std::string&, const int, const int, const int, const bool);
    int getDamage(void);
};

class Armor : public Item {
    int def;

public:
    void print() const;
    Armor(const std::string&, const int, const int, const int);
};

class Potion : public Item {
    const cstats potion_type; //which stat to increase
    const int buffAmount = 5;
    std::string typeToString() const;

public:
    void print() const;
    void buff(Hero&);
    Potion(const std::string&, const int, const int, cstats);
};

class Spell : public Item { //make abstract
protected:
    const int min_dmg, max_dmg, mp_cost;
    const int duration;
    std::string typeToString();

public:
    virtual void print() const;
    virtual void apply_effect(Monster*) = 0;
    int getSpellDmg(void) const;
    int getMPcost(void) const;
    Spell(const std::string&, const int, const int, const int, const int, const int, const int);
};

class IceSpell : public Spell {
public:
    void print() const;
    void apply_effect(Monster*);
    IceSpell(const std::string&, const int, const int, const int, const int, const int, const int);
};

class FireSpell : public Spell {
public:
    void print() const;
    void apply_effect(Monster*);
    FireSpell(const std::string&, const int, const int, const int, const int, const int, const int);
};

class LightningSpell : public Spell {
public:
    void print() const;
    void apply_effect(Monster*);
    LightningSpell(const std::string&, const int, const int, const int, const int, const int, const int);
};

//////////////////////////////////////////////////////////////////////////////////////
class Living {
protected:
    std::string Name;
    int Level;
    int HealthPower;
    bool Faint;

public:
    Living(const std::string, const int);
    virtual ~Living() = 0;

    void decrease_hp(int);

    std::string get_name() const;
    int get_hp() const;
    virtual void print() const = 0;
    void pass_out();
};

class Hero : public Living {
protected:
    int MagicPower;
    int Strength;
    int Dexterity;
    int Agility;
    int Money;
    int Experience;
    int XPmax;
    std::vector<Potion*> potions;
    std::vector<Spell*> spells;
    //Weapon* MyWeapon;
    //Armor* MyArmor;
    //Potion* MyPotion;
    std::vector<Item*> inv;

public:
    void print() const;
    Hero(const std::string, int, int, int);
    virtual ~Hero() = 0;
    void set_xp(const int);
    int get_agility() const;
    int getMoney() const;
    int& getStat(cstats);
    void castSpell(Monster*, int);
    void attack(Monster*);
    virtual void levelUp() = 0;
    virtual void levelUp(int, int, int);
    void addToInv(Item*);
};

class Warrior : public Hero {
public:
    Warrior(const std::string);
    ~Warrior();
    void levelUp();
};

class Sorcerer : public Hero {
public:
    Sorcerer(const std::string);
    ~Sorcerer();

    void levelUp();
};

class Paladin : public Hero {
public:
    Paladin(const std::string);
    ~Paladin();

    void levelUp();
};

class Monster : public Living {
protected:
    int minDMG;
    int maxDMG;
    int Defense;
    int Dodge;
    std::map<spellType, int> debuffStatus; //map type to spell dur

public:
    void print() const;
    Monster(const std::string, int, int, int, int);
    virtual ~Monster() = 0;
    int get_defense() const;
    int get_dodge() const;
    void debuff(spellType, int);
    void attack(Hero*);
};

class Dragon : public Monster {
public:
    Dragon(const std::string);
    ~Dragon();
};

class Exoskeleton : public Monster {
public:
    Exoskeleton(const std::string);
    ~Exoskeleton();
};

class Spirit : public Monster {
public:
    Spirit(const std::string);
    ~Spirit();
};

//////////////////////////////////////////////////////////////////////////////////////////

class block {
protected:
    std::vector<Hero*> squad;

public:
    virtual void print() const = 0;
    virtual void move(std::vector<Hero*>&) = 0;
};

class market : public block {
    std::vector<Item*> items;

public:
    void move(std::vector<Hero*>&);
    void display(); //display shop
    void print() const; //print as 'M' on map
    void purchase(Hero&, int);
    market();
    ~market();
};

class common : public block {
    bool end_fight(const std::vector<Monster*>&);
    void fight(std::vector<Monster*>&);

public:
    void displayStatus(const std::vector<Monster*>&) const;
    void print() const;
    void move(std::vector<Hero*>&);
    void fight_start();
};

class inaccessible : public block {
public:
    void print() const;
    void move(std::vector<Hero*>& squad);
    Monster* m;
};

#endif