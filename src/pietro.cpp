#include "pietro.h"

Pietro::Pietro()
{
}

Pietro::~Pietro(){
    delete[] pokoje;
}

void Pietro::setNumerPietra(int numerPietra){
    this->numerPietra=numerPietra;
}

void Pietro::setLiczbaPokoi(int liczbaPokoi){
    this->liczbaPokoi=liczbaPokoi;
    this->pokoje=new Pokoj[liczbaPokoi];
}

int Pietro::getNumerPietra(){
    return this->numerPietra;
}

int Pietro::getLiczbaPokoi(){
    return this->liczbaPokoi;
}

Pokoj* Pietro::getPokoje(){
    return pokoje;
}

int Pietro::getRoomIndexByNumber(int number){
    for(int i=0;i<liczbaPokoi;i++){
        if(number==pokoje[i].getNumerPokoju()){
            return i;
        }
    }
    return -1;
}
