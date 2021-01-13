//  File Name:  monster.cpp

#include "rpg_lib.hpp"

using std::string;

Monster::~Monster()
{
    //cout << "A Monster to be destroyed!" <'\n';
    std::cout << Name << '\n';
    std::cout << "Level: " << Level << '\n';
    std::cout << "HP: " << HealthPower
              << "\n\n";
    std::cout << "DMG: " << minDMG << " - " << maxDMG << '\n';
    std::cout << "DEF: " << Defense << '\n';
    std::cout << "DODGE: " << Dodge << "%" << '\n';
    std::cout << std::endl;
}

Monster::Monster(const string MyName, int LowDMG, int HighDMG, int DEF, int MissChance, int LvL)
    : minDMG(LowDMG)
    , maxDMG(HighDMG)
    , Defense(DEF)
    , Dodge(MissChance)
    , Living(MyName, LvL * 20, LvL)
    , debuffStatus { { spellType::ICE, 0 }, { spellType::FIRE, 0 }, { spellType::LIGHTNING, 0 } } //spelltype and round duration
{
}

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
    if (rand() % 100 > MyHero->get_agility()) {
        std::cout << get_name() << " dealt " << DMGdealt << " DMG to " << MyHero->get_name() << "!" << '\n';
        MyHero->decrease_hp(DMGdealt);
    } else
        std::cout << MyHero->get_name() << " DODGED the Attack!" << '\n';
    std::cout << MyHero->get_name() << " HP is: " << MyHero->get_hp() << std::endl;
}

void Monster::debuff(spellType st, int rounds)
{
    //debuff lasts for + rounds
    //add round_start(),round_end()
    if (debuffStatus.find(st)->second == 0) { //apply effect if not already applied
        if (st == spellType::ICE) {
            maxDMG -= 5;
        } else if (st == spellType::FIRE) {
            Defense -= 5;
        } else {
            Dodge -= 5;
        }
    }
    debuffStatus[st] += rounds;
}

void Monster::resetStats()
{
    for (auto& stats : debuffStatus) {
        if (stats.second > 0) { //check rounds passed since spell effect applied
            --stats.second;
            if (stats.second == 0) { //reset stats to normal if x rounds passed
                if (stats.first == spellType::ICE) {
                    maxDMG += 5;
                } else if (stats.first == spellType::FIRE) {
                    Defense += 5;
                } else {
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