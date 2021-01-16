#ifndef RPG_H
#define RPG_H
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Hero;
class Monster;
class Market;
class block;

enum class blockType
{
    COMMON,
    INACCESSIBLE
};

enum class heroType {
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

enum class gearType {
    ARMOR,
    RWEAPON,
    LWEAPON
};

class Item {
public:
    virtual void print() const = 0;
    virtual ~Item() = default;

protected:
    const std::string name;
    const int buy_price;
    const int min_level;

public:
    Item(const std::string&, const int, const int);
    std::string get_name() const;
    int getPrice() const;
    int get_minlvl() const;
};

class Weapon : public Item {
    const int dmg;
    const bool two_handed;

public:
    void print() const;
    Weapon(const std::string&, const int, const int, const int, const bool);
    int getDamage(void) const;
    std::string get_grip() const;
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

public:
    int get_buff_amount() const;
    std::string typeToString() const;
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
    int get_mindmg() const;
    int get_maxdmg() const;
    int getSpellDmg(void) const;
    int getMPcost(void) const;
    int get_duration() const;
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
    int MaxHealthPower; //changes on levelup
    int HealthPower;
    bool Faint;

public:
    Living(const std::string&, const int, int = 1);
    virtual ~Living() = 0;
    void regenHP();
    void decrease_hp(int);
    int getLevel();
    std::string get_name() const;
    int get_hp() const;
    virtual void displayStats() const = 0;
    void pass_out();
    ///potions//
};

class Hero : public Living {
protected:
    //Max increases on levelup
    int MagicPower, MaxMagicPower;
    int Strength, MaxStr;
    int Dexterity, MaxDex;
    int Agility, MaxAgil;
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
    void addMoney(int);
    //void sell(market&);
    void displayStats() const;
    Hero(const std::string&, int, int, int, Weapon*, Armor*, Spell*);
    void moneyLoss();
    virtual ~Hero() = 0;
    void revive();
    void set_xp(const int);
    void regenMP();

    //  Accessors
    int get_strength() const;
    int get_dexterity() const;
    int get_agility() const;
    int getMoney() const;
    Weapon* get_righthand() const;
    Weapon* get_lefthand() const;
    Armor* get_armor() const;
    int& getStat(potionType);
    int get_max_xp() const;
    int get_vector_size(std::string) const;

    void attack(Monster*);
    void castSpell(Monster*, int);

    void use(int);

    virtual void levelUp() = 0;
    virtual void levelUp(int, int, int);

    void set_weapon(int, int = 1);
    void equip(int);
    void unequip(gearType);
    void DisplayItems(std::string) const;
    void checkInventory() const;
    //
    void buy(Weapon*);
    void buy(Armor*);
    void buy(Potion*);
    void buy(Spell*);
    void sell(Market*, std::string, int);
    char proceed();

    void HPbuff(int);
    void MPbuff(int);
    void STRbuff(int);
    void DEXbuff(int);
    void AGILbuff(int);
};

class Warrior : public Hero {
public:
    Warrior(const std::string&, Weapon*, Armor*, Spell*);
    ~Warrior();

    void levelUp();
};

class Sorcerer : public Hero {
public:
    Sorcerer(const std::string&, Weapon*, Armor*, Spell*);
    ~Sorcerer();

    void levelUp();
};

class Paladin : public Hero {
public:
    Paladin(const std::string&, Weapon*, Armor*, Spell*);
    ~Paladin();

    void levelUp();
};

class Monster : public Living {
protected:
    int minDMG;
    int maxDMG;
    int Defense;
    int Dodge;
    std::array<int, 3> debuffDur; //hold dur for each debuff..

public:
    void displayStats() const;
    Monster(const std::string&, int, int, int, int, int);
    virtual ~Monster() = 0;

    int get_defense() const;
    int get_dodge() const;

    void debuff(spellType, int);
    void attack(Hero*);
    void finish_round();
};

class Dragon : public Monster {
public:
    Dragon(const std::string&, int = 1);
    ~Dragon();
};

class Exoskeleton : public Monster {
public:
    Exoskeleton(const std::string&, int = 1);
    ~Exoskeleton();
};

class Spirit : public Monster {
public:
    Spirit(const std::string&, int = 1);
    ~Spirit();
};

/////////////////////////////////////////////////////////////////////

class Market
{
    private:
        int size;
        std::vector<Weapon*> weapons;
        std::vector<Armor*> armors;
        std::vector<Potion*> potions;
        std::vector<Spell*> spells;
    public:
        Market(std::vector<Weapon*>, std::vector<Armor*>, std::vector<Potion*>, std::vector<Spell*>);
        ~Market();

        int get_vector_size(std::string) const;
        void DisplayItems(std::string) const;
        void buy(Hero*, std::string, int);
        void sell(Weapon*);
        void sell(Armor*);
        void sell(Potion*);
        void sell(Spell*);
};

class Block
{
    protected:
        Market* MyMarket;
        std::vector<Hero*> Squad;
        std::vector<Monster*> Enemies;
        blockType type;
    public:
        Block(blockType);
        virtual ~Block() = 0;

        Market* get_market() const;
        virtual void move(std::vector<Hero*>) = 0;
        virtual void print() const = 0;
        blockType get_type() const; 

};

class Common : public Block
{
    public:
        Common(blockType);
        Common(blockType, std::vector<Weapon*>, std::vector<Armor*>, std::vector<Potion*>, std::vector<Spell*>);
        ~Common();

        void move(std::vector<Hero*>);
        void fight_start();
        void print() const;
};

class Inaccessible : public Block
{
    public:
        Inaccessible(blockType);
        ~Inaccessible();

        void move(std::vector<Hero*>);
        void print() const;
};

//////////////////////////////////////////////////////////////////////////////////////////

/*
class common : public block {
    void end_round(std::vector<Monster*>&);
    bool end_fight(const std::vector<Monster*>&); //check if time to end fight
    void fight(std::vector<Monster*>&);

public:
    void displayStats(const std::vector<Monster*>&) const;
    void fight_start();
};
*/

class Game {
private:
    int input;
    bool playing;
    int Dimension;
    int ActiveBlock_x;
    int ActiveBlock_y;
    int ActiveHero;
    std::array<std::array<Block*, 8>, 8> Grid;

    std::vector<Weapon*> AllWeapons;
    std::vector<Armor*> AllArmors;
    std::vector<Potion*> AllPotions;
    std::vector<Spell*> AllSpells;
    std::vector<Hero*> MyHeroes;

public:
    Game();
    virtual ~Game();

    void StartScreen();
    void ExitScreen();

    //  DI_RPG Menu
    void DIRPG();
    void NewHeroMenu();
    void CreditsScreen();

    //  Initialization
    void InitGame();
    void InitWeapons();
    void InitArmors();
    void InitPotions();
    void InitSpells();
    void InitMonsters();
    void InitGrid();

    //  New Hero Menu
    void WarriorInfo();
    void SorcererInfo();
    void PaladinInfo();
    void CreateNewHero(heroType);

    //  Block Menu
    void CommonBlockMenu();
    void InventoryMenu();
    void MoveMenu();
    void MarketMenu();
    void MainMenu();

    //  Inventory Menu
    void ChangeWeapon();
    void ChangeArmor();
    void UsePotion();

    //  Move Menu


    //  Market Menu
    void BuyMenu();
    void SellMenu();
    void BuyWeapons();
    void BuyArmors();
    void BuyPotions();
    void BuySpells();
    void SellWeapons();
    void SellArmors();
    void SellPotions();
    void SellSpells();

    //  Main Menu
    /*void HeroesInfoMenu();*/
    /*void ChangeActiveHero();*/
    void DisplayMap();

    //  Clear Functions
    void static clearscreen();
    void static clearbuffer();

    //  Accessors
    bool get_playing() const;
};

#endif
