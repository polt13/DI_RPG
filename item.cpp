#include "rpg_lib.hpp"

using std::string;

Item::Item(const string& _name, const int price, const int lvl)
    : name(_name)
    , buy_price(price)
    , min_level(lvl)
{
}

string Item::get_name() const
{
    return name;
}

int Item::getPrice() const
{
    return buy_price;
}

int Item::get_minlvl() const
{
    return min_level;
}

Weapon::Weapon(const string& _name, const int price, const int lvl, const int damage, const bool grip)
    : Item(_name, price, lvl)
    , dmg(damage)
    , two_handed(grip)
{
}

void Weapon::print() const
{
    std::cout << name << " | Price: " << buy_price << " | Damage: " << dmg << (two_handed == true ? " | Two Handed" : " | One Handed") << " | Minimum level: " << min_level << std::endl;
}

int Weapon::getDamage(void) const
{
    return dmg;
}

std::string Weapon::get_grip() const
{
    if (two_handed == true)
        return "Two Handed";
    return "One Handed";
}

bool Weapon::isTwoHanded() const
{
    return two_handed;
}

Armor::Armor(const string& _name, const int price, const int lvl, const int defense)
    : Item(_name, price, lvl)
    , def(defense)
{
}

int Armor::get_def() const
{
    return def;
}

void Armor::print() const
{
    std::cout << name << " | Price: " << buy_price << " | Defense: " << def << " | Minimum level: " << min_level << std::endl;
}

// make the enum-type printable
string Potion::typeToString() const
{
    switch (potion_type) {
    case (potionType::HP):
        return "HP";
    case (potionType::MP):
        return "MP";
    case (potionType::AGIL):
        return "AGIL";
    case (potionType::DEX):
        return "DEXT";
    case (potionType::STR):
        return "STR";
    }
    return "BAD_TYPE";
}

Potion::Potion(const string& _name, const int price, const int lvl, potionType type)
    : Item(_name, price, lvl)
    , potion_type(type)
{
}

int Potion::get_buff_amount() const
{
    return buffAmount;
}

void Potion::print() const
{
    std::cout << name << " | Price: " << buy_price << " | Buff: " << typeToString() << " | Buff Amount: " << buffAmount << " | Minimum level: " << min_level << std::endl;
}
void Potion::buff(Hero* h)
{
    if (potion_type == potionType::HP) {

        std::cout << h->get_name() << " uses potion and replenishes " << buffAmount << " HP\n";
        h->HPbuff(buffAmount);
    } else if (potion_type == potionType::MP) {
        std::cout << h->get_name() << " uses potion and replenishes " << buffAmount << " MP\n";
        h->MPbuff(buffAmount);
    } else if (potion_type == potionType::AGIL) {
        std::cout << h->get_name() << " uses potion and replenishes " << buffAmount << " AGILITY\n";
        h->AGILbuff(buffAmount);
    } else if (potion_type == potionType::DEX) {
        std::cout << h->get_name() << " uses potion and replenishes " << buffAmount << " DEXTERITY\n";
        h->DEXbuff(buffAmount);
    } else {
        std::cout << h->get_name() << " uses potion and replenishes " << buffAmount << " STRENGTH\n";
        h->STRbuff(buffAmount);
    }
}

Spell::Spell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Item(_name, price, lvl)
    , min_dmg(mindmg)
    , max_dmg(maxdmg)
    , duration(dur)
    , mp_cost(mp) {};

int Spell::get_mindmg() const
{
    return min_dmg;
}

int Spell::get_maxdmg() const
{
    return max_dmg;
}

int Spell::get_duration() const
{
    return duration;
}

int Spell::getMPcost(void) const
{
    return mp_cost;
}

int Spell::getSpellDmg(void) const
{
    return (std::rand() % (max_dmg - min_dmg + 1) + min_dmg);
}

void Spell::print() const
{
    std::cout << name << " | Price: " << buy_price << " | Damage Range: " << min_dmg << " - " << max_dmg << " | MP cost: " << mp_cost << " | Duration: " << duration << " | Minimum level: " << min_level;
}

IceSpell::IceSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

void IceSpell::apply_effect(Monster* m)
{
    m->ice_debuff(duration);
}

void IceSpell::print() const
{
    Spell::print();
    std::cout << " [ Ice Spell ]" << std::endl;
}
FireSpell::FireSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

void FireSpell::print() const
{
    Spell::print();
    std::cout << " [ Fire Spell ]" << std::endl;
}

void FireSpell::apply_effect(Monster* m)
{
    m->fire_debuff(duration);
}

LightningSpell::LightningSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

void LightningSpell::print() const
{
    Spell::print();
    std::cout << " [ Lightning Spell ]" << std::endl;
}
void LightningSpell::apply_effect(Monster* m)
{
    m->li_debuff(duration);
}
