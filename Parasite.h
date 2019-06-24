#ifndef PARASITE_H_INCLUDED
#define PARASITE_H_INCLUDED

class Parasite
{
private:
    double age;

public:
    Parasite();
    ~Parasite();

    void aging(double _ageInterval);
    void die();

    double getAge();
};

#endif // PARASITE_H_INCLUDED
