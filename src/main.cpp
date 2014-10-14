#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pietro.h"

using namespace std;

Pietro* pietra;
int liczbaPieter=0;

void zapiszBaze(Pietro* pietra, int liczbaPieter){
    FILE *plik;
    if((plik=fopen("rajd_elektryka.txt","wt"))!=NULL){
        fprintf(plik, "%d\n", liczbaPieter);
        for(int i=0;i<liczbaPieter;i++){
            fprintf(plik, "%d\n", pietra[i].getNumerPietra());
            fprintf(plik, "%d\n", pietra[i].getLiczbaPokoi());
            for(int j=0;j<pietra[i].getLiczbaPokoi();j++){
                fprintf(plik, "%d\n", pietra[i].getPokoje()[j].getNumerPokoju());
                fprintf(plik, "%d\n", pietra[i].getPokoje()[j].getLiczbaMiejsc());
                for(int k=0;k<pietra[i].getPokoje()[j].getLiczbaMiejsc();k++){
                    fprintf(plik, "%s\n", pietra[i].getPokoje()[j].getOsobaZPokoju(k)->getOsoba());
                }
            }
        }
        fclose(plik);
    }
}

Pokoj* getRoomPtrByNumber(int number){
    for(int i=0;i<liczbaPieter;i++){
        for(int j=0;j<pietra[i].getLiczbaPokoi();j++){
            if(number==pietra[i].getPokoje()[j].getNumerPokoju()){
                return &(pietra[i].getPokoje()[j]);
            }
        }
    }

    return -1;
}

void oknoGlowne(int liczbaPieter, Pietro* pietra){
    int rzedy, kolumny, kolumny15, x, y, wybor;
    char input[10];
    Pokoj* aktualny;

    do{
        clear();
        WINDOW* okno;

        okno=initscr();
        start_color();

        curs_set(0);

        init_pair(1, COLOR_BLACK, COLOR_WHITE); //czarne litery
        init_pair(2, COLOR_WHITE, COLOR_BLACK); //białe litery

        init_pair(3, COLOR_BLACK, COLOR_GREEN); //zielone tło
        init_pair(4, COLOR_BLACK, COLOR_YELLOW); //zółte tło
        init_pair(5, COLOR_BLACK, COLOR_RED);   //czerwone tło

        init_pair(6, COLOR_WHITE, COLOR_BLUE); //białe na niebieskim

        wattrset(okno,COLOR_PAIR(6));

        mvprintw(0,0,"Kwatermistrz3000 - wygodne kwaterowanie na Rajdzie Elektryka\n");

        wattrset(okno,COLOR_PAIR(2));

        //noecho();

        getmaxyx( stdscr, rzedy, kolumny );
        kolumny15=kolumny/15;

        x=0;
        y=1;

        for(int i=0;i<liczbaPieter;i++){
            move(y,x);
            printw("Pietro %d, pokoi %d",pietra[i].getNumerPietra(), pietra[i].getLiczbaPokoi());
            for(int j=0;j<pietra[i].getLiczbaPokoi();j++){
                if(j%kolumny15==0){
                    y++;
                    x=0;
                }
                move(y,x);
                float wspolczynnik=(float)(((float)(pietra[i].getPokoje()[j].getLiczbaZajetychMiejsc()))/((float)(pietra[i].getPokoje()[j].getLiczbaMiejsc())));
                if(wspolczynnik>0.7){
                    wattrset(okno,COLOR_PAIR(5));
                }
                else
                if(wspolczynnik>0.4){
                    wattrset(okno,COLOR_PAIR(4));
                }
                else{
                    wattrset(okno,COLOR_PAIR(3));
                }
                printw("%d    %d/%d",pietra[i].getPokoje()[j].getNumerPokoju(), pietra[i].getPokoje()[j].getLiczbaZajetychMiejsc(), pietra[i].getPokoje()[j].getLiczbaMiejsc());
                wattrset(okno,COLOR_PAIR(2));
                x+=15;
            }
            y++;
            x=0;
        }

        mvprintw(rzedy-1,0,"Dostepne komendy: zapisz, koniec (nie zapisuje danych!)");
        mvprintw(rzedy-2,0,"Podaj numer pokoju do edycji lub komende: ");

        //refresh();

        getstr(input);
        if(!(strcmp(input,"zapisz"))){
            zapiszBaze(pietra, liczbaPieter);
        }else
        if(!(strcmp(input,"koniec"))){
            delete[] pietra;
            return;
        }
        wybor=atoi(input);

        aktualny=getRoomPtrByNumber(wybor);
        if(aktualny!=-1){
            char znak;
            char nazwisko[20];
            int pozycja=0;
            while(true){
                clear();
                noecho();
                getmaxyx( stdscr, rzedy, kolumny );
                mvprintw(rzedy-2,0,"Nawigacja strzalkami: lewo - wroc do pieter, prawo - edycja podswietlonego miejsca, gora/dol - zmiana miejsca");
                x=0;
                y=0;
                wattrset(okno,COLOR_PAIR(6));

                mvprintw(0,0,"Kwatermistrz3000 - wygodne kwaterowanie na Rajdzie Elektryka\n");

                wattrset(okno,COLOR_PAIR(2));
                y++;
                x=0;
                mvprintw(y,x,"Pokój numer %d zajete %d/%d miejsc", aktualny->getNumerPokoju(), aktualny->getLiczbaZajetychMiejsc(), aktualny->getLiczbaMiejsc());
                for(int i=0;i<aktualny->getLiczbaMiejsc();i++){
                    y++;
                    x=0;
                    if(i==pozycja){
                        attron( A_REVERSE );
                        mvprintw(y,x,"%d. %s",i+1, aktualny->getOsobaZPokoju(i)->getOsoba());
                        attroff( A_REVERSE );
                    }else{
                        mvprintw(y,x,"%d. %s",i+1, aktualny->getOsobaZPokoju(i)->getOsoba());
                    }
                }

                znak=getch();

                if (znak == '\033') { // if the first value is esc
                    getch(); // skip the [
                    switch(getch()) { // the real value
                        case 'A' :  if(pozycja>0){
                                        pozycja--;
                                    }
                                    break;
                        case 'B':   if(pozycja<aktualny->getLiczbaMiejsc()-1){
                                        pozycja++;
                                    }
                                    break;
                        case 'C':   y=2+pozycja;
                                    if(pozycja>8){
                                        x=4;
                                    }else{
                                        x=3;
                                    }
                                    move(y,x);
                                    printw("                     ");
                                    move(y,x);
                                    curs_set(1);
                                    echo();
                                    getstr(nazwisko);
                                    curs_set(0);
                                    aktualny->getOsobaZPokoju(pozycja)->setOsoba(nazwisko);
                                    if(nazwisko[0]!='\0'){
                                        aktualny->getOsobaZPokoju(pozycja)->setStan(true);
                                    }
                                    else{
                                        aktualny->getOsobaZPokoju(pozycja)->setStan(false);
                                    }
                                    break;
                        case 'D':   goto wyjscie;
                                    break;
                        default: break;
                    }
                }
            }
        }
        wyjscie:
        echo();
    }
    while(true);
}

int main()
{
    int wybor;

    cout << "Witaj w programie Kwatermistrz3000 służącym do sprawnego kwaterowania uczestników Rajdu Elektryka. Zanim przejdziesz do głównego okna programu musisz stworzyć strukturę ośrodka lub wczytać już zapisaną." << endl;
    cout << "Aby stworzyć nową strukturę wciśnij 1" << endl;
    cout << "Aby wczytać zapisaną bazę wciśnij 2" << endl;
    cin >> wybor;
    if(wybor==1){
        int numerPokoju, liczbaMiejsc;
        cout << "Podaj liczbę pięter w ośrodku:" << endl;
        cin >> liczbaPieter;
        pietra=new Pietro[liczbaPieter];
        for(int i=0;i<liczbaPieter;i++){
            int numerPietra, liczbaPokoi;
            cout << "Podaj numer piętra pod jakim ma się wyświetlać w programie:" << endl;
            cin >> numerPietra;
            pietra[i].setNumerPietra(numerPietra);
            cout << "Podaj liczbę pokoi na piętrze:" << endl;
            cin >> liczbaPokoi;
            pietra[i].setLiczbaPokoi(liczbaPokoi);
        }

        for(int i=0;i<liczbaPieter;i++){
            for(int j=0;j<pietra[i].getLiczbaPokoi();j++){
                cout << "Podaj numer " << j+1 << ". z kolei pokoju na piętrze " << pietra[i].getNumerPietra() << ".:" <<endl;
                cin >> numerPokoju;
                cout << "Podaj liczbę miejsc w pokoju " << numerPokoju << " na piętrze " << pietra[i].getNumerPietra() << ".:" <<endl;
                cin >> liczbaMiejsc;
                pietra[i].getPokoje()[j].setPokoj(numerPokoju, liczbaMiejsc);
            }
        }

        oknoGlowne(liczbaPieter, pietra);

        endwin();
    }
    else
    if(wybor==2){
        FILE *plik;
        if((plik=fopen("rajd_elektryka.txt","rt"))!=NULL){
            fscanf(plik, "%d", &liczbaPieter);
            pietra=new Pietro[liczbaPieter];
            for(int i=0;i<liczbaPieter;i++){
                int numerPietra, liczbaPokoi;
                fscanf(plik, "%d", &numerPietra);
                pietra[i].setNumerPietra(numerPietra);
                fscanf(plik, "%d", &liczbaPokoi);
                pietra[i].setLiczbaPokoi(liczbaPokoi);
                for(int j=0;j<liczbaPokoi;j++){
                    int numerPokoju, liczbaMiejsc;
                    char nazwisko[22];
                    fscanf(plik, "%d", &numerPokoju);
                    fscanf(plik, "%d", &liczbaMiejsc);
                    pietra[i].getPokoje()[j].setPokoj(numerPokoju, liczbaMiejsc);
                    fgets(nazwisko, 2, plik);
                    for(int k=0;k<liczbaMiejsc;k++){
                        fgets(nazwisko, 22, plik);
                        char *lamanieLinii=NULL;
                        lamanieLinii=strchr(nazwisko,'\n');
                        if(*lamanieLinii){
                            *lamanieLinii='\0';
                        }
                        if(nazwisko[0]!='\0'){
                            pietra[i].getPokoje()[j].getOsobaZPokoju(k)->setOsoba(nazwisko);
                            pietra[i].getPokoje()[j].getOsobaZPokoju(k)->setStan(true);
                        }
                    }
                }
            }
            fclose(plik);
        }

        oknoGlowne(liczbaPieter, pietra);

        endwin();
    }
    else{
        cout << "Niestety nie umiesz się ładnie bawić jak inne dzieci. Do widzenia!" << endl;
    }

    return 0;
}

