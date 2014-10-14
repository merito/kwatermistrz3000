#include <string.h>
#include "osoba.h"

Osoba::Osoba(){
    this->stan=false;
    this->nazwa=new char[20];
}

Osoba::~Osoba(){
    delete[] this->nazwa;
}

char* Osoba::getOsoba(){
    return this->nazwa;
}

bool Osoba::getStan(){
    return this->stan;
}

void Osoba::setOsoba(char *nazwa){
    memcpy(this->nazwa,nazwa,sizeof(char)*20);
}

void Osoba::setStan(bool stan){
    this->stan=stan;
}
