#include <string.h>
#include "osoba.h"

Osoba::Osoba(){
    this->stan=false;
    this->nazwa=new char[50];
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
    memcpy(this->nazwa,nazwa,sizeof(char)*50);
}

void Osoba::setStan(bool stan){
    this->stan=stan;
}
