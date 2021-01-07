#include "rpg_lib.hpp"

using std::string;

Item::Item(const string& _name, const int price, const int lvl)
    : name(_name)
    , buy_price(price)
    , min_level(lvl)
{
}

int Item::getPrice() const
{
    return buy_price;
}

Weapon::Weapon(const string& _name, const int price, const int lvl, const int damage, const bool grip)
    : Item(_name, price, lvl)
    , dmg(damage)
    , two_handed(grip)
{
}

void Weapon::print() const
{
    std::cout << " Weapon:\n"
              << name << "Price: " << buy_price << " Damage: " << dmg << (two_handed == true ? " Two Handed " : " One Handed ") << " Minimum level req. : " << min_level << std::endl;
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

void Armor::print() const
{
    std::cout << " Armor:\n"
              << name << "Price: " << buy_price << " Defense: " << def << " Minimum level req. : " << min_level << std::endl;
}

string Potion::typeToString() const
{
    switch (potion_type) {
    case (cstats::HP):
        return "HP";
    case (cstats::MP):
        return "MP";
    case (cstats::AGIL):
        return "AGIL";
    case (cstats::DEX):
        return "DEXT";
    case (cstats::STR):
        return "STR";
    }
    return "BAD_TYPE";
}

Potion::Potion(const string& _name, const int price, const int lvl, cstats type)
    : Item(_name, price, lvl)
    , potion_type(type)
{
}

void Potion::print() const
{
    std::cout << " Potion:\t"
              << name << "Price: " << buy_price << " Buff: " << typeToString() << " Buff Amount: " << buffAmount << " Minimum level req : " << min_level << std::endl;
}
void Potion::buff(Hero& h)
{
    int& statToIncrease = h.getStat(potion_type);
    //get Hero's stat by reference and increase it
    statToIncrease += buffAmount;
}

Spell::Spell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Item(_name, price, lvl)
    , min_dmg(mindmg)
    , max_dmg(maxdmg)
    , duration(dur)
    , mp_cost(mp) {};

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
    std::cout << name << "Price: " << buy_price << " Max Damage: " << max_dmg << " Min. Damage: " << min_dmg << " Max Damage: " << max_dmg << " MP cost: " << mp_cost << " Duration: " << duration << "Minimum level req : " << min_level << std::endl;
}

IceSpell::IceSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

void IceSpell::apply_effect(Monster* m)
{
    m->debuff(spellType::ICE, duration);
}

void IceSpell::print() const
{
    std::cout << "Ice Spell\t";
    Spell::print();
}
FireSpell::FireSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

void FireSpell::print() const
{
    std::cout << "Fire Spell\t";
    Spell::print();
}

void FireSpell::apply_effect(Monster* m)
{
    m->debuff(spellType::FIRE, duration);
}

LightningSpell::LightningSpell(const string& _name, const int price, const int lvl, const int mindmg, const int maxdmg, const int mp, const int dur)
    : Spell(_name, price, lvl, mindmg, maxdmg, mp, dur)
{
}

void LightningSpell::print() const
{
    std::cout << "Lightning Spell\t";
    Spell::print();
}
void LightningSpell::apply_effect(Monster* m)
{
    m->debuff(spellType::LIGHTNING, duration); //debuff type and how long it lasts
}
///////////////////////////////////

market::market()
{
    long int item_count = std::rand() % 6 + 5;
    for (int i = 1; i <= item_count; ++i) {
        items.push_back(new Potion("Item", rand() % 10, 5, cstats::HP));
    }
}

void market::purchase(Hero& h, int whichItemToBuy)
{
    if (items[whichItemToBuy]->getPrice() <= h.getMoney()) {
        h.addToInv(items[whichItemToBuy]);
        items.erase(items.begin() + whichItemToBuy); //remove from shop
    } else {
        std::cout << "not enough money\n";
        return;
    }
}