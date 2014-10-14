#ifndef PIETRO_H
#define PIETRO_H

#include "pokoj.h"

class Pietro
{
public:
    Pietro();
    ~Pietro();
    void setNumerPietra(int numerPietra);
    void setLiczbaPokoi(int liczbaPokoi);
    int getNumerPietra();
    int getLiczbaPokoi();
    Pokoj* getPokoje();
    int getRoomIndexByNumber(int number);
private:
    int numerPietra;
    int liczbaPokoi;
    Pokoj *pokoje;
};

#endif // PIETRO_H
