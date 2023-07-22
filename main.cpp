//
// Created by xglas on 26.10.21.
//
#include <iostream>
#include "Hra.h"


int main() {
    Hra *moje = Hra::getHra();
    moje->infooMeste();
    moje->vypisPravidla();
    moje->vyberAkci();
    delete moje;
    return 0;
}




