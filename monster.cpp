//  File Name:  monster.cpp

#include "rpg_lib.hpp"

using std::string;

Monster::~Monster()
{
    //cout << "A Monster to be destroyed!" <'\n';
   std::cout<< Name <<'\n';
   std::cout<< "Level: " << Level << '\n';
   std::cout<< "HP: " << HealthPower
        <<"\n\n";
   std::cout<< "DMG: " << minDMG << " - " << maxDMG <<'\n';
   std::cout<< "DEF: " << Defense <<'\n';
   std::cout<< "DODGE: " << Dodge << "%" <<'\n';
   std::cout << std::endl;
}

Monster::Monster(const string MyName, int LowDMG, int HighDMG, int DEF, int MissChance)
    : minDMG(LowDMG)
    , maxDMG(HighDMG)
    , Defense(DEF)
    , Dodge(MissChance)
    , Living(MyName, 250),debuffStatus{{spellType::ICE,0},{spellType::FIRE,0},{spellType::LIGHTNING,0}}
{
    //cout << "A New Monster has been created!" <'\n';
   std::cout<< Name <<'\n';
   std::cout<< "Level: " << Level <<'\n';
   std::cout<< "HP: " << HealthPower <<"\n\n";
   std::cout<< "DMG: " << minDMG << " - " << maxDMG <<'\n';
   std::cout<< "DEF: " << Defense <<'\n';
   std::cout<< "DODGE: " << Dodge << "%" <<'\n';
   std::cout<< std::endl;
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
    if (MyHero->get_armor() != NULL)
        DMGdealt = (rand() % (maxDMG - minDMG + 1) + minDMG) - MyHero->get_armor()->get_def(); //Generate num from minDMG-maxDMG included
    else
        DMGdealt = (rand() % (maxDMG - minDMG + 1) + minDMG);
    if (DMGdealt < 0)
    {
        std::cout << "Higher defense than dmg\n";
        return;
    }
    if (rand() % 100 > MyHero->get_agility())
    {
        std::cout<< get_name() << " dealt " << DMGdealt << " DMG to " << MyHero->get_name() << "!" <<'\n';
        MyHero->decrease_hp(DMGdealt);
    }
    else
        std::cout<< MyHero->get_name() << " DODGED the Attack!" <<'\n';
   std::cout<< MyHero->get_name() << " HP is: " << MyHero->get_hp() << std::endl;
}

void Monster::debuff(spellType st, int rounds)
{
    debuffStatus[st]+=rounds; //debuff lasts for + rounds
    //add round_start(),round_end()
}

///////////////////////////////////////////////////////////////////////////////////////////////