//
// Created by Uzivatel on 12.11.2021.
//

#include "Hra.h"

Hra *Hra::s_instance = nullptr;


Hra::Hra(std::string nazevMesta, std::string jmenoStarosty, int obtiznost) {
    m_mesto = new Mesto(std::move(nazevMesta));
    m_starosta = new Starosta(std::move(jmenoStarosty));
    m_XP = 500;
    m_lvl = 1;
    m_lvlQuests = new Level(obtiznost);
    m_moznostiStaveb.push_back(new Stavba(0, true));
    m_moznostiStaveb.push_back(new Stavba(1, true));
}

void Hra::uvodniNastaveni(std::string &nazevMesta, std::string &jmenoStarosty, int &obtiznost) {
    std::cout << "Ahoj Starosto, jak se jmenujes?" << std::endl;
    std::cin >> jmenoStarosty;
    std::cout << "To je dobre jmeno pro Starostu. Jak se bude jmenovat Tve mesto?" << std::endl;
    std::cin >> nazevMesta;
    while (!(obtiznost >= 1 && obtiznost <= 10)) {
        std::cout << "Vyber si obtiznost 1-10:" << std::endl;
        std::cin >> obtiznost;
        if (!(obtiznost >= 1 && obtiznost <= 10))
            std::cout << "Takova obtiznost neexistuje, zkus to znovu." << std::endl;
    }
}

Hra *Hra::getHra() {
    if (Hra::s_instance == nullptr) {
        int obtiznost = 0;
        std::string jmenoStarosty, nazevMesta;
        Hra::uvodniNastaveni(nazevMesta, jmenoStarosty, obtiznost);
        return new Hra(nazevMesta, jmenoStarosty, obtiznost);
    } else {
        return Hra::s_instance;
    }
}

Hra::~Hra() {
    delete m_mesto;
    delete m_starosta;
}

void Hra::pridejXP(int XP) {
    m_XP += XP;
}

void Hra::odeberXP(int XP) {
    m_XP -= XP;
}

void Hra::kontrolaXP() {
    float pom = (double) m_mesto->getNezamestnanost() / m_mesto->getPocetObyvatel();
    int xp = m_mesto->getPocetObyvatel() * (m_mesto->getSpokojenost() / pom);
    //std::cout<<"Pomocna"<< pom << " xp "<<xp <<std::endl;
    pridejXP(xp);
}

bool Hra::dostatekXP(Stavba *stavba) {
    bool hodnota = false;
    if (m_XP >= stavba->getCena()) hodnota = true;
    return hodnota;
}

void Hra::kontrolaLvl() {
    int puvodni_lvl = m_lvl;
    m_lvl = m_lvlQuests->dosazenyLvl(m_mesto->getBudovyPocty());
    if (puvodni_lvl != m_lvl) {
        naucStavbu();
    }
}

void Hra::naucStavbu() {
    m_moznostiStaveb.push_back(new Stavba(m_lvl, true));
}

void Hra::postavStavbu(int druh) {
    int x, y;
    std::cout << "Na jake souradnice chces budovu postavit?" << std::endl;
    m_mesto->zobrazMesto();
    std::cout << "Zadej souradnici x (radek): ";
    std::cin >> x;
    std::cout << "\nZadej souradnici y (sloupec): ";
    std::cin >> y;
    x--;
    y--;
    if (x > 19 || y > 19) {
        std::cout << "Zadal si rozmer mimo pole" << std::endl;
        return;
    }
    auto *newstavba = new Stavba(druh, jeUSilnice(x, y));
    if (druh == 2 && (((m_mesto->druhBudovyNaPozici(x - 1, y) >= 0 && m_mesto->getUSilnice(x - 1, y))
                       || (m_mesto->druhBudovyNaPozici(x + 1, y) >= 0 && m_mesto->getUSilnice(x + 1, y))
                       || (m_mesto->druhBudovyNaPozici(x, y - 1) >= 0 && m_mesto->getUSilnice(x, y - 1))
                       || (m_mesto->druhBudovyNaPozici(x, y + 1) >= 0 && m_mesto->getUSilnice(x, y + 1)))) &&
        Hra::dostatekXP(newstavba)) {
        m_mesto->vyplnPole(newstavba, x, y);
        Hra::odeberXP(newstavba->getCena());
        m_mesto->setBudovu(druh);
        Hra::kontrolaLvl();
    } else if ((!Hra::jeUSilnice(x, y) || m_mesto->druhBudovyNaPozici(x, y) != -1)) {
        std::cout
                << "\nNemuzes stavet stavbu, ktera neni u silnice, ani park, ktery neni u jine stavby. Take nejde stavet na obsazenem miste."
                << std::endl;
        return;
    } else if (!Hra::dostatekXP(newstavba)) {
        std::cout << "\nMalo XP" << std::endl;
        delete newstavba;
    } else {
        m_mesto->vyplnPole(newstavba, x, y);
        Hra::odeberXP(newstavba->getCena());
        m_mesto->setBudovu(druh);
        Hra::kontrolaLvl();
        if (druh == 0) { m_mesto->silniceON(x, y); } // novee --- obnova cest pokud by byly rozpojeny...

    }

}

void Hra::vyberAkci() {
    int c, a = 0;
    while (a == 0) {
        //aby se aktualizoval stav mesta v prubehu hry
        m_mesto->setPocetObyvatel();
        m_mesto->setNezamestnanost();
        m_mesto->setSpokojenost(m_mesto->spocitejPrirustekSpokojenosti());
        kontrolaLvl();
        std::cout << std::endl << "LEVEL: " << m_lvl << " XP: " << m_XP << "  [";
        std::cout << "Populace: " << m_mesto->getPocetObyvatel() << " Spokojenost: " << m_mesto->getSpokojenost()
                  << " Nezamestnanost: " << m_mesto->getNezamestnanost() - 1 << "]" << std::endl;
        std::cout << "------------------------------------------------------------------" << std::endl;
        std::cout << "Vyberte jednu z nasledujicich moznosti: " << std::endl;
        std::cout << "1. postavit stavbu" << std::endl;
        std::cout << "2. zbourat stavbu" << std::endl;
        std::cout << "3. vypsat mapu" << std::endl;
        std::cout << "4. pridat XP (pridat XP jde jen za predpokladu nedostatku XP na postaveni nejlevnejsi budovy)"
                  << std::endl;
        std::cout << "5. pravidla" << std::endl;
        std::cout << "6. ukoncit hru" << std::endl;
        std::cin >> c;
        switch (c) {
            case 1:
                Hra::vyberBudovu();
                break;
            case 2:
                int x, y;
                std::cout << "Na jake pozici chces zbourat budovu? \n Zadej radek: ";
                std::cin >> x;
                std::cout << "\n Zadej sloupec: ";
                std::cin >> y;
                if (x > 20 || y > 20) {
                    std::cout << "Zadal si rozmer mimo pole" << std::endl;
                    break;
                } else
                    Hra::zbouratBudovu(--x, --y);
                break;
            case 3:
                m_mesto->zobrazMesto();
                break;
            case 4:
                if (m_XP < 100)
                    kontrolaXP();
                else
                    std::cout << "Mas jeste dostatek XP na to postavit aspon silnici" << std::endl;
                break;
            case 5:
                vypisPravidla();
                break;
            case 6:
                a = 1;
                break;
            default:
                std::cout << "Neni takova moznost zkus to znovu" << std::endl;

        }
    };
}

void Hra::vyberBudovu() {
    int id;
    std::cout << "LEVEL: " << m_lvl << " XP: " << m_XP << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Kterou budovu chces postavit?" << std::endl;
    for (int i = 0; i < m_moznostiStaveb.size(); i++) {
        std::cout << i + 1 << ". " << m_moznostiStaveb.at(i)->getPopis() << std::endl;
    }
    std::cin >> id;
    if (id > m_moznostiStaveb.size()) {
        std::cout << "Zkus to jeste jednou" << std::endl;
        std::cin >> id;
    }
    switch (id) {
        case 1:
            Hra::postavStavbu(0);
            break;
        case 2:
            Hra::postavStavbu(1);
            break;
        case 3:
            if (m_lvl < 2)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(2);
            break;
        case 4:
            if (m_lvl < 3)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(3);
            break;
        case 5:
            if (m_lvl < 4)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(4);
            break;
        case 6:
            if (m_lvl < 5)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(5);
            break;
        case 7:
            if (m_lvl < 6)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(6);
            break;
        case 8:
            if (m_lvl < 7)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(7);
            break;
        case 9:
            if (m_lvl < 8)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(8);
            break;
        case 10:
            if (m_lvl < 9)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(9);
            break;
        case 11:
            if (m_lvl < 10)
                std::cout << "Nemuzes postavit tuto budovu" << std::endl;
            else
                Hra::postavStavbu(10);
            break;
        default:
            std::cout << "Nespravna volba" << std::endl;
    }
}

bool Hra::jeUSilnice(int x, int y) {
    return ((m_mesto->druhBudovyNaPozici(x - 1, y) == 0 && m_mesto->getUSilnice(x - 1, y))
            || (m_mesto->druhBudovyNaPozici(x + 1, y) == 0 && m_mesto->getUSilnice(x + 1, y))
            || (m_mesto->druhBudovyNaPozici(x, y - 1) == 0 && m_mesto->getUSilnice(x, y - 1))
            || (m_mesto->druhBudovyNaPozici(x, y + 1) == 0 && m_mesto->getUSilnice(x, y + 1)));
}

void Hra::zbouratBudovu(int x, int y) {

    if (x == 9 && y == 0) {
        std::cout << std::endl << "Na teto pozici nejde bourat" << std::endl;
        return;
    }

    int druh = m_mesto->druhBudovyNaPozici(x, y); //nove
    m_mesto->vyplnPole(nullptr, x, y);
    if (druh == 0)  //nove
    {
        m_mesto->silniceOFF();
        m_mesto->silniceON(9, 0);
    }
}

void Hra::vypisPravidla() {
    std::cout << "Ahoj starosto! \nV nasi hre budes moct stavet a bourat budovy ve svem meste. Cilem je dostat se do "
                 "12. lvl a mit moznost postavit vsechny typy budov. \n---Budovy te budou stat nejake XP, ktere si budes moct sam pridat az, kdyz"
                 " nebudes moct postavit zadnou stavbu (silnice stoji 100 XP). \n---Vsechny budovy musi stat u silnice. Vyjimkou je park, ktery jako jediny"
                 " muze stat u jine budovy stranou od silnice.\n"
                 "---POZOR, vsechny silnice musi byt napojene na prvni Silnici. Pokud zbouras silnici, ktera jine spojuje,"
                 " u odpojenych silnic nepujde stavet, dokud je zpet nepripojis. \n"
                 "---XP se odviji od poctu obyvatel, nezamestnanosti a spokojenosti.\n"
                 "Pravidla si muzes znovu zobrazit zavolanim prikazu \"5. Pravidla\" v zakladnim vyberu." << std::endl;
}

void Hra::infooMeste() {
    std::cout << std::endl << "Jmeno mesta: " << Hra::m_mesto->getNazev() << std::endl;
    std::cout << "Jmeno starosty: " << Hra::m_starosta->getJmeno() << std::endl;
}


