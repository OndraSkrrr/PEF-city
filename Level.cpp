//
// Created by Ondra on 24.11.2021.
//

#include "Level.h"
#include "time.h"
#include "stdlib.h"
#include <iostream>

Level::Level(int hardness) {
    if (hardness < 1 || hardness > 10) hardness = 4; //kontroluje primerenou obtiznost
    srand(time(NULL));
    for (int i = 0; i < 11; i++) m_lvlReq.at(0).at(i) = 0; //prvni level ma hrac instantne, pozadavky na nej jsou nulove
    for (int j = 1; j < 11; j++)   // projde vsechny rady
    {
        for (int k = 0; k <= j; k++) //projde vsechny prvky v radku (vsechny sloupce)
        {
            m_lvlReq.at(j).at(k) = m_lvlReq.at(j - 1).at(k) + rand() % hardness +
                                   1; //pozadavek na budovy je v kazdem levlu alespon takovy jako v predchozim levlu, nebo vetsi o nahodnou hodnotu
        }
        for (int k = j + 1; k < 11; k++)
            m_lvlReq.at(j).at(k) = 0; //predchozi cyklus vzdy prida o jeden pozadavek na level vic, zbytek ma byt nulovy
    }
}

void Level::vypis() {
    for (int i = 0; i < 11; i++) {
        for (int k = 0; k < 11; k++) {
            std::cout << m_lvlReq.at(i).at(k) << " ";
        }
        std::cout << std::endl;
    }
}

bool Level::arrayCompare(std::array<int, 11> vekt1, std::array<int, 11> vekt2) {
    bool jeVetsiRoven = true;
    for (int i = 0; i < 11; i++) {
        if (vekt1.at(i) < vekt2.at(i))
            jeVetsiRoven = false; //pokud je v jakekoliv slozce vekt1 mensi je to automaticky false
    }
    return jeVetsiRoven;
}

int Level::dosazenyLvl(std::array<int, 11> myCity) {
    int reachedLvl = 0;
    for (int i = 0; i < 11; i++) {
        if (arrayCompare(myCity, m_lvlReq.at(i))) reachedLvl = (i + 1);
    }
    return reachedLvl;
}