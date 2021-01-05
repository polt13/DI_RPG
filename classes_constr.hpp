//  File Name:  classes_constr.hpp

class Living
{
    protected:
        std::string Name;
        int Level;
        int HealthPower;
        bool Faint;
    public:
        Living(const std::string, const int);
        virtual ~Living() = 0;

        void decrease_hp(int);

        std::string get_name();
        int get_hp();

        void pass_out();
};

class Hero: public Living
{
    protected:
        int MagicPower;
        int Strenght;
        int Dexterity;
        int Agility;
        int Money;
        int Experience;
        int XPmax;
    public:
        Hero(const std::string, int, int, int);
        virtual ~Hero() = 0;

        int get_agility();

        void set_xp(const int);

        virtual void levelUp(int, int, int);
};

class Warrior: public Hero
{
    public:
        Warrior(const std::string);
        ~Warrior();

        void levelUp();
};

class Sorcerer: public Hero
{
    public:
        Sorcerer(const std::string);
        ~Sorcerer();

        void levelUp();
};

class Paladin: public Hero
{
    public:
        Paladin(const std::string);
        ~Paladin();

        void levelUp();
};

class Monster: public Living
{
    protected:
        int minDMG;
        int maxDMG;
        int Defense;
        int Dodge;
    public:
        Monster(const std::string, int, int, int, int);
        virtual ~Monster() = 0;

        void attack(Hero*);
};

class Dragon: public Monster
{
    public:
        Dragon(const std::string);
        ~Dragon();
};

class Exoskeleton: public Monster
{
    public:
        Exoskeleton(const std::string);
        ~Exoskeleton();
};

class Spirit: public Monster
{
    public:
        Spirit(const std::string);
        ~Spirit();
};