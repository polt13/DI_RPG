#include "item.hpp"

using std::string;

Item::Item(const string& _name, const int price, const int lvl)
    : name(_name)
    , buy_price(price)
    , min_level(lvl)
{
}

Item::~Item() { }

void Item::print(void) { std::cout << "Item Name: "
                                   << " Buy Price: " << buy_price << " Min.Level: " << min_level; }

Weapon::Weapon(const string& _name, const int price, const int lvl, const int damage, const bool grip)
    : Item(_name, price, lvl)
    , dmg(damage)
    , two_handed(grip)
{
}

int Weapon::getDamage(void)
{
    return dmg;
}

Armor::Armor(const string& _name, const int price, const int lvl, const int defense)
    : Item(_name, price, lvl)
    , def(defense)
{
}

Potion::Potion(const string& _name, const int price, const int lvl, cstats type)
    : Item(_name, price, lvl)
    , potion_type(type)
{
}

void Potion::buff(Hero& h)
{
    if (potion_type == cstats::AGIL) {
        
    }
}

Spell::Spell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Item(_name, price, lvl)
    , min_dmg(mindmg)
    , max_dmg(maxdmg)
    , duration(dur)
    , mp_cost(mp) {};

IceSpell::IceSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

FireSpell::FireSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

LightningSpell::LightningSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}
