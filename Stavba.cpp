//
// Created by xglas on 09.11.21.
//

#include "Stavba.h"

Stavba::Stavba(int druh, bool uSilnice) {
    m_druh = druh;
    switch (druh) {
        case 0:
            m_druh = 0;
            m_cena = 100;
            m_popis = "Silnice";
            break;
        case 1:
            m_druh = 1;
            m_cena = 150;
            m_popis = "Dum";
            break;
        case 2:
            m_druh = 2;
            m_cena = 300;
            m_popis = "Park";
            break;
        case 3:
            m_druh = 3;
            m_cena = 250;
            m_popis = "Policie";
            break;
        case 4:
            m_druh = 4;
            m_cena = 350;
            m_popis = "Zachranka";
            break;
        case 5:
            m_druh = 5;
            m_cena = 400;
            m_popis = "Kultura";
            break;
        case 6:
            m_druh = 6;
            m_cena = 450;
            m_popis = "Hasici";
            break;
        case 7:
            m_druh = 7;
            m_cena = 250;
            m_popis = "Tovarna";
            break;
        case 8:
            m_druh = 8;
            m_cena = 350;
            m_popis = "Obchod";
            break;
        case 9:
            m_druh = 9;
            m_cena = 500;
            m_popis = "Elektrarna";
            break;
        case 10:
            m_druh = 10;
            m_cena = 550;
            m_popis = "Vodarna";
            break;
    }
    m_uSilnice = uSilnice;
}

bool Stavba::getUSilnice() {
    return m_uSilnice;
}

int Stavba::getDruh() {
    return m_druh;
}

int Stavba::getCena() {
    return m_cena;
}

void Stavba::setUSilnice(bool uSilnice) {
    m_uSilnice = uSilnice;
}

std::string Stavba::getPopis() {
    return m_popis;
}
