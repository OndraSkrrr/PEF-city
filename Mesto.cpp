//
// Created by Uživatel on 10.11.2021.
//

#include "Mesto.h"
#include "iostream"
#include "array"
#include "Hra.h"

Mesto::Mesto(std::string nazev) {
    m_nazev = nazev;
    m_pocetObyvatel = 1; //vzdy alespon starosta = OCHRANA PROTI DELENI nulou
    m_spokojenost = 100.0;
    m_nezamestnost = 1;
    m_budovyPocty.at(0) = 1;
    for (int i = 1; i < m_budovyPocty.size(); i++) m_budovyPocty.at(i) = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 9 && j == 0)
                mapa[i][j] = new Stavba(0, true);
            else
                mapa[i][j] = nullptr;
        }
    }
}

Mesto::~Mesto() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 9 && j == 0)
                delete mapa[i][j];
        }
    }
};

void Mesto::vyplnPole(Stavba *stavba, int x, int y) {
    mapa[x][y] = stavba;
}

void Mesto::zobrazMesto() {
    int pom;
    std::cout
            << "     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19    20"
            << std::endl;
    for (int i = 0; i < 20; i++) {
        if (i < 9)
            std::cout << i + 1 << " |";
        else
            std::cout << i + 1 << "|";
        for (int j = 0; j < 20; j++) {
            if (mapa[i][j] == nullptr)
                std::cout << "     ";
            else {
                pom = mapa[i][j]->getDruh();
                if (!mapa[i][j]->getUSilnice()) { std::cout << "~"; } else { std::cout << " "; }
                std::cout << prevedBudovu(pom);
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}

int Mesto::druhBudovyNaPozici(int x, int y) {
    if (mapa[x][y] == nullptr)
        return -1;
    else
        return mapa[x][y]->getDruh();
}

bool Mesto::getUSilnice(int x, int y) {
    if (mapa[x][y] == nullptr) {
        return false;
    } else {
        return mapa[x][y]->getUSilnice();
    }
}

void Mesto::setSpokojenost(float prirustek) {
    if (Mesto::m_spokojenost + prirustek > 100) {
        Mesto::m_spokojenost = 100;
    } else {
        Mesto::m_spokojenost += prirustek;
    }
}

void Mesto::setBudovu(int druh) {
    m_budovyPocty[druh]++;
}

void Mesto::setNezamestnanost() {
    int pozic = 0;
    pozic = m_budovyPocty.at(3) * 5 + m_budovyPocty.at(4) * 6
            + m_budovyPocty.at(6) * 6 + m_budovyPocty.at(7) * 30
            + m_budovyPocty.at(8) * 8;
    if (pozic >= m_pocetObyvatel) {
        m_nezamestnost = 1;
    } else {
        m_nezamestnost = (m_pocetObyvatel - pozic);
    }
    if (m_nezamestnost < 0)
        m_nezamestnost = 1;
}

std::string Mesto::getNazev() {
    return m_nazev;
}

void Mesto::setPocetObyvatel() {
    m_pocetObyvatel = 1 + m_budovyPocty.at(1) * 5;  //musi byt vzdy alespon 1, jinak hrozi deleni nulou
}

float Mesto::getSpokojenost() {
    return m_spokojenost;
}

int Mesto::getNezamestnanost() {
    return m_nezamestnost;
}

int Mesto::getPocetObyvatel() {
    return m_pocetObyvatel;
}

//<0.1, protoze je jedna policie na 10 domu
//podobne i dalsi pomery v ifech viz readme
float Mesto::spocitejPrirustekSpokojenosti() {

    float prirustek = 0;
    int m_pocetDomu = 0;
    for (int i = 1; i < m_budovyPocty.size(); i++)
        m_pocetDomu += m_budovyPocty[i];
    if (m_pocetDomu != 0) {   // na zacatku hry, kdy nejsou domy by nastalo deleni nulou a pad aplikace
        float policieDomy = m_budovyPocty.at(3) / m_pocetDomu;
        float hasiciDomy = m_budovyPocty.at(6) / m_pocetDomu;
        float obchodyDomy = m_budovyPocty.at(8) / m_pocetDomu;
        if (policieDomy < 0.1) {
            prirustek -= policieDomy * 2; //neni uplne ok, smaze to vsechno za desetinnou carkou, ale...
        }
        if (hasiciDomy < 0.05) {
            prirustek -= hasiciDomy;
        }
        if (obchodyDomy < 0.04) {
            prirustek -= obchodyDomy * 5;
        }
        prirustek += (m_budovyPocty.at(2) * 0.02);
        prirustek += (m_budovyPocty.at(5) * 0.03);
    }
    //std::cout << "Prirustek spokojenosti: " << prirustek << std::endl;
    return prirustek;
}

std::array<int, 11> Mesto::getBudovyPocty() {
    return m_budovyPocty;
}

std::string Mesto::prevedBudovu(int id) {
    switch (id) {
        case 0:
            return "sil ";
        case 1:
            return "dum ";
        case 2:
            return "park";
        case 3:
            return "poli";
        case 4:
            return "ZZS ";
        case 5:
            return "kult";
        case 6:
            return "hasi";
        case 7:
            return "tova";
        case 8:
            return "obch";
        case 9:
            return "elek";
        case 10:
            return "voda";

    }
    return "bad";
}

void Mesto::silniceOFF() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (mapa[i][j] != nullptr) {
                if (mapa[i][j]->getDruh() != -1) {
                    mapa[i][j]->setUSilnice(false);
                }
            }
        }
    }
}

void Mesto::silniceON(int x, int y) {
    if (mapa[x][y] != nullptr && mapa[x][y]->getDruh() == 0) {
        mapa[x][y]->setUSilnice(true);
    }
    if (mapa[x - 1][y] != nullptr && mapa[x - 1][y]->getDruh() == 0 && !mapa[x - 1][y]->getUSilnice()) {
        silniceON(x - 1, y);
    }
    if (mapa[x + 1][y] != nullptr && mapa[x + 1][y]->getDruh() == 0 && !mapa[x + 1][y]->getUSilnice()) {
        silniceON(x + 1, y);
    }
    if (mapa[x][y - 1] != nullptr && mapa[x][y - 1]->getDruh() == 0 && !mapa[x][y - 1]->getUSilnice()) {
        silniceON(x, y - 1);
    }
    if (mapa[x][y + 1] != nullptr && mapa[x][y + 1]->getDruh() == 0 && !mapa[x][y + 1]->getUSilnice()) {
        silniceON(x, y + 1);
    }

    if (mapa[x - 1][y] != nullptr && mapa[x - 1][y]->getDruh() > 0 && !mapa[x - 1][y]->getUSilnice()) {
        mapa[x - 1][y]->setUSilnice(true);
    }
    if (mapa[x + 1][y] != nullptr && mapa[x + 1][y]->getDruh() > 0 && !mapa[x + 1][y]->getUSilnice()) {
        mapa[x + 1][y]->setUSilnice(true);
    }
    if (mapa[x][y - 1] != nullptr && mapa[x][y - 1]->getDruh() > 0 && !mapa[x][y - 1]->getUSilnice()) {
        mapa[x][y - 1]->setUSilnice(true);
    }
    if (mapa[x][y + 1] != nullptr && mapa[x][y + 1]->getDruh() > 0 && !mapa[x][y + 1]->getUSilnice()) {
        mapa[x][y + 1]->setUSilnice(true);
    }
}