#ifndef RPG_H
#define RPG_H
#include <iostream>
#include <string>
#include <vector>
class Hero;
enum class cstats { DEX,
    STR,
    AGIL,
    HP,
    MP };

class Item {
protected:
    const std::string name;
    const int buy_price;
    const int min_level;
    Item(const std::string&, const int, const int);
    virtual ~Item() = 0; //make abstract
    void print();
};

class Weapon : public Item {
    const int dmg;
    const bool two_handed;

public:
    Weapon(const std::string&, const int, const int, const int, const bool);
    int getDamage(void);
};

class Armor : public Item {
    int def;

public:
    Armor(const std::string&, const int, const int, const int);
};

class Potion : public Item {
    const cstats potion_type; //which stat to increase
    const int buffAmount = 5;

public:
    void buff(Hero&);
    Potion(const std::string&, const int, const int, cstats);
};

class Spell : public Item { //make abstract
    const int min_dmg, max_dmg, mp_cost;
    const int duration;

public:
    int getSpellDmg(void);
    int getMPcost(void);
    Spell(const std::string&, const int, const int, const int, const int, const int, const int);
};

class IceSpell : public Spell {
public:
    IceSpell(const std::string&, const int, const int, const int, const int, const int, const int);
};

class FireSpell : public Spell {
public:
    FireSpell(const std::string&, const int, const int, const int, const int, const int, const int);
};

class LightningSpell : public Spell {
public:
    LightningSpell(const std::string&, const int, const int, const int, const int, const int, const int);
};

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

    std::string get_name();
    int get_hp();

    void pass_out();
};

class Monster;

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
    //vector se items
public:
    Hero(const std::string, int, int, int);
    virtual ~Hero() = 0;

    void set_xp(const int);

    int get_agility() const;
    //int get_weap_dmg() const;
    //int get_armor_def() const;
    int& getStat(cstats);
    void castSpell(Monster*, int);
    void attack(Monster*);
    virtual void levelUp() = 0;
    virtual void levelUp(int, int, int);
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

public:
    Monster(const std::string, int, int, int, int);
    virtual ~Monster() = 0;

    int get_defense();
    int get_dodge();

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
#endif