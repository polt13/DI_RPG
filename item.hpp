#include <iostream>
#include <string>

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