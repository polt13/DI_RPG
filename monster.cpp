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
        std::cout << "Attack has no effect: Hero has higher DEFENSE!\n";
        return;
    }
    if ((std::rand() % 100) > MyHero->get_agility()) {
        std::cout << get_name() << " dealt " << DMGdealt << " DMG to " << MyHero->get_name() << "!" << '\n';
        MyHero->decrease_hp(DMGdealt);
    } else
        std::cout << MyHero->get_name() << " DODGED the Attack!" << '\n';
    std::cout << MyHero->get_name() << " HP is: " << MyHero->get_hp() << std::endl;
}

void Monster::ice_debuff(int rounds)
{
    if (debuffDur[0] == 0) {
        std::cout << "Ice spell debuff: Damage is reduced by 5\n";
        maxDMG -= 5;
        minDMG -= 5;
    }

    debuffDur[0] += rounds;
    std::cout << "Debuff lasts for " << debuffDur[0] << " rounds\n";
}

void Monster::fire_debuff(int rounds)
{
    if (debuffDur[1] == 0) {
        std::cout << " Fire spell debuff: Armor is  reduced by 5\n";
        Defense -= 5;
    }

    debuffDur[1] += rounds;
    std::cout << "Debuff lasts for " << debuffDur[1] << " rounds\n";
}

void Monster::li_debuff(int rounds)
{
    if (debuffDur[2] == 0) {
        std::cout << " Lightning spell debuff: Dodge is reduced by 5\n";
        Dodge -= 5;
    }
    debuffDur[2] += rounds;
    std::cout << "Debuff lasts for " << debuffDur[2] << " rounds\n";
}

void Monster::finish_round()
{
    for (auto i = 0; i < debuffDur.size(); i++) {
        if (debuffDur[i] > 0) {
            {
                --debuffDur[i];
                //checks if debuff effect duration has come to an end
                if (debuffDur[i] == 0) {
                    if (i == 0) {
                        std::cout << "Effect of -DMG has worn out for " << Name << '\n';
                        maxDMG += 5;
                        minDMG += 5;
                    } else if (i == 1) {
                        std::cout << "Effect of -DEF has worn out for " << Name << '\n';
                        Defense += 5;
                    } else {
                        std::cout << "Effect of -DODGE has worn out for " << Name << '\n';
                        Dodge += 5;
                    }
                }
            }
        }
    }
}

void Monster::displayStats() const
{
    std::cout << Name << " | "
              << " HP: "
              << HealthPower << " | DMG: " << minDMG << '-' << maxDMG << " | DEF: " << Defense << " | DODGE: " << Dodge << '\t';
    if (HealthPower == 0) {
        std::cout << "- Fainted!\n";
    }
}
