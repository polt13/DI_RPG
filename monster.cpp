//  File Name:  monster.cpp

#include "rpg_lib.hpp"

using std::string;

Monster::Monster(const string& MyName, int LowDMG, int HighDMG, int DEF, int MissChance, int LvL)
    : minDMG(LowDMG)
    , maxDMG(HighDMG)
    , Defense(DEF)
    , Dodge(MissChance)
    , Living(MyName, LvL * 20, LvL)

{
    debuffDur.fill(0); //spelltype and round duration
}

Monster::~Monster() { }

int Monster::get_defense() const
{
    return Defense;
}

int Monster::get_dodge() const
{
    return Dodge;
}

void Monster::attack(Hero* MyHero)
{
    if (MyHero->get_hp() == 0)
        return;
    int DMGdealt;
    if (MyHero->get_armor() != nullptr)
        DMGdealt = (std::rand() % (maxDMG - minDMG + 1) + minDMG) - MyHero->get_armor()->get_def(); //Generate num from minDMG-maxDMG included
    else
        DMGdealt = (std::rand() % (maxDMG - minDMG + 1) + minDMG);
    if (DMGdealt < 0) {
        std::cout << "Higher defense than dmg\n";
        return;
    }
    if ((std::rand() % 100) > MyHero->get_agility()) {
        std::cout << get_name() << " dealt " << DMGdealt << " DMG to " << MyHero->get_name() << "!" << '\n';
        MyHero->decrease_hp(DMGdealt);
    } else
        std::cout << MyHero->get_name() << " DODGED the Attack!" << '\n';
    std::cout << MyHero->get_name() << " HP is: " << MyHero->get_hp() << std::endl;
}

void Monster::debuff(spellType st, int rounds)
{
    //debuff lasts for + rounds
    // i = 0 for dur of ice, i =1 dur of fire, i=2 dur of lightning

    switch (st) {
    case spellType::ICE:
        //only apply the debuff once, if it's casted again only increase debuff duration
        if (debuffDur[0] == 0) {
            std::cout << "Ice spell debuff: Damage is reduced by 5\n";
            maxDMG -= 5;
        }

        debuffDur[0] += rounds;
        std::cout << "Debuff lasts for " << debuffDur[0] << '\n';
        break;
    case spellType::FIRE:
        if (debuffDur[1] == 0) {
            std::cout << " Fire spell debuff: Armor is  reduced by 5\n";
            Defense -= 5;
        }

        debuffDur[1] += rounds;
        std::cout << "Debuff lasting for " << debuffDur[0] << '\n';
        break;
    case spellType::LIGHTNING:
        if (debuffDur[2] == 0) {
            std::cout << " Lightning spell debuff: Dodge is reduced by 5\n";
            Dodge -= 5;
        }
        debuffDur[2] += rounds;
        std::cout << "Debuff lasting for " << debuffDur[0] << '\n';
        break;
    }
}

void Monster::finish_round()
{
    for (auto i = 0; i < debuffDur.size(); i++) {
        if (debuffDur[i] > 0) {
            {
                debuffDur[i]--;
                //checks if debuff effect duration has come to an end
                if (debuffDur[i] == 0) {
                    if (i == 0) {
                        maxDMG += 5;
                    } else if (i == 1) {
                        Defense += 5;
                    } else
                        Dodge += 5;
                }
            }
        }
    }
}

void Monster::displayStats() const
{
    std::cout << Name << " HP: " << HealthPower << '\t';
}

///////////////////////////////////////////////////////////////////////////////////////////////