#ifndef RPG_H
#define RPG_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Hero;
class Monster;


enum class heroType
{
    WARRIOR,
    SORCERER,
    PALADIN
};

enum class potionType { DEX,
    STR,
    AGIL,
    HP,
    MP };

enum class spellType {
    ICE,
    FIRE,
    LIGHTNING
};

enum class ItemType
{
    WEAPON,
    ARMOR,
    POTION,
    SPELL
};

enum class gearType {
    ARMOR,
    RWEAPON,
    LWEAPON
};

class Item {
public:
    virtual void print() const = 0;

protected:
    const std::string name;
    const int buy_price;
    const int min_level;
    const ItemType ITYPE;

public:
    Item(const std::string&, const int, const int, const ItemType);
    std::string get_name() const;
    int getPrice() const;
    int get_minlvl() const;
    ItemType get_itype() const;
};

class Weapon : public Item {
    const int dmg;
    const bool two_handed;

public:
    void print() const;
    Weapon(const std::string&, const int, const int, const int, const bool);
    int getDamage(void) const;
    bool isTwoHanded() const;
};

class Armor : public Item {
    int def;

public:
    int get_def() const;
    void print() const;
    Armor(const std::string&, const int, const int, const int);
};

class Potion : public Item {
    const potionType potion_type; //which stat to increase
    const int buffAmount = 5;
    std::string typeToString() const;

public:
    void print() const;
    void buff(Hero&);
    Potion(const std::string&, const int, const int, potionType);
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
    const std::string Name;
    int Level;
    int HealthPower;
    bool Faint;

public:
    Living(const std::string, const int, int = 1);
    virtual ~Living() = 0;

    void decrease_hp(int);

    std::string get_name() const;
    int get_hp() const;
    virtual void displayStats() const = 0;
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
    Weapon* RightHand;
    Weapon* LeftHand;
    Armor* MyArmor;
    std::vector<Weapon*> WeaponsInv;
    std::vector<Armor*> ArmorsInv;
    std::vector<Potion*> PotionsInv;
    std::vector<Spell*> SpellsInv;

public:
    void displayStats() const;
    Hero(const std::string, int, int, int);
    virtual ~Hero() = 0;

    void set_xp(const int);

    //  Accessors
    int get_strength() const;
    int get_dexterity() const;
    int get_agility() const;
    int getMoney() const;
    Armor* get_armor() const;
    int& getStat(potionType);
    int get_max_xp();

    void attack(Monster*);
    void castSpell(Monster*, int);

    void use(int);

    virtual void levelUp() = 0;
    virtual void levelUp(int, int, int);

    void set_weapon(int, int = 1);
    void equip(int);
    void unequip(gearType);
    void checkInventory() const;
    void addToInv(Weapon*);
    void addToInv(Armor*);
    void addToInv(Potion*);
    void addToInv(Spell*);
    char proceed();
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
    void displayStats() const;
    Monster(const std::string, int, int, int, int, int);
    virtual ~Monster() = 0;

    int get_defense() const;
    int get_dodge() const;

    void debuff(spellType, int);
    void attack(Hero*);
};

class Dragon : public Monster {
public:
    Dragon(const std::string, int = 1);
    ~Dragon();
};

class Exoskeleton : public Monster {
public:
    Exoskeleton(const std::string, int = 1);
    ~Exoskeleton();
};

class Spirit : public Monster {
public:
    Spirit(const std::string, int = 1);
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
    std::vector<Armor*> armorStock;
    std::vector<Weapon*> weaponStock;
    std::vector<Spell*> spellStock;
    std::vector<Potion*> potionStock;

public:
    void move(std::vector<Hero*>&);
    void display(); //display shop
    void print() const; //print as 'M' on map
    void purchase(Hero&);
    market();
    ~market();
};

class common : public block {
    bool end_fight(const std::vector<Monster*>&);
    void fight(std::vector<Monster*>&);

public:
    void displayStats(const std::vector<Monster*>&) const;
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

class Game
{
    private:
        int input;
        bool playing;

        int ActiveHero;
        std::vector<Hero*> MyHeroes;

        std::vector<Weapon*> AllWeapons;
        std::vector<Armor*> AllArmors;
        std::vector<Potion*> AllPotions;
        std::vector<Spell*> AllSpells;

        std::vector<block*> Grid[16];
    public:
        Game();
        virtual ~Game();

        void StartScreen();
        void ExitScreen();

        //  DI_RPG Menu
        void DIRPG();
        void MainMenu();
        void CreditsScreen();

        //  Initialization
        void InitGame();
        void InitWeapons();
        void InitArmors();
        void InitPotions();
        void InitSpells();
        void InitGrid();

        //  Main Menu
        void NewHeroMenu();
        void DisplayMarket();
        void printWeap();
        
        void DisplayMap();

        //  New Hero Menu
        void WarriorInfo();
        void SorcererInfo();
        void PaladinInfo();
        void CreateNewHero(heroType);

        //  Market Menu
        void BuyMenu();
        void SellMenu();
        void BuyWeapons();
        void BuyArmors();
        void BuyPotions();
        void BuySpells();

        //  Clear Functions
        void clearscreen() const;
        void clearbuffer();

        //  Accessors
        bool get_playing() const;
};

#endif