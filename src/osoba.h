#ifndef OSOBA_H
#define OSOBA_H

class Osoba
{
public:
    Osoba();
    ~Osoba();
    char* getOsoba();
    bool getStan();
    void setOsoba(char* nazwa);
    void setStan(bool stan);
private:
    char* nazwa;
    bool stan;
};

#endif // OSOBA_H
