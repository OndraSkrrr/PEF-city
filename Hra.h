//
// Created by Uživatel on 12.11.2021.
//
#include "Stavba.h"
#include "Mesto.h"
#include "Starosta.h"
#include "Level.h"
#include "vector"

/**
 * @authors xsmikmat, xskrob, xglas
 * @brief Hlavní třída pro hlídání funkcí celé hry.
 */
class Hra {
    int m_XP;
    int m_lvl;
    static Hra *s_instance;
    Starosta *m_starosta;
    Mesto *m_mesto;
    Level *m_lvlQuests;
    std::vector<Stavba *> m_moznostiStaveb;

    Hra(std::string nazevMesta, std::string jmenoStarosty, int obtiznost);

public:
    /**
     * Singleton.
     * @return Instance Hry.
     */
    static Hra *getHra();

    ~Hra();

    /**
     * Počáteční nastavení informací o hře.
     * @param nazevMesta - zadaný název města na vstupu
     * @param jmenoStarosty - zadané jméno starosty na vstupu
     * @param obtiznost - obtížnost na vstupu
     */
    static void uvodniNastaveni(std::string &nazevMesta, std::string &jmenoStarosty, int &obtiznost);

    /**
     * Navýší m_xp o zadané xp.
     * @param XP - o kolik se zvyšuje
     */
    void pridejXP(int XP);

    /**
     * Zmenší m_xp o zadané xp.
     * @param XP - o kolik se snižuje
     */
    void odeberXP(int XP);

    /**
     * Vypočte, o kolik se má navýšit m_xp a provede navýšení.
     */
    void kontrolaXP();

    /**
     * Zjistí, zda je na postavení dané budovy dost XP.
     * @param stavba - pro kterou stavbu kontrolujeme
     * @return Jestli má hráč dostatek XP na stavbu.
     */
    bool dostatekXP(Stavba *stavba);

    /**
     * Zkontroluje, na jaký level hráč dosahuje a daný level nastaví.
     */
    void kontrolaLvl();

    /**
     * Naučí se postavit novou stavbu.
     */
    void naucStavbu();

    /**
     * Pokud je dost XP, postaví danou stavbu na pozici [x,y], jinak vypíše chybu.
     * @param druh - jakou stavbu stavíme
     */
    void postavStavbu(int druh);

    /**
     * Hlavní metoda pro dění ve hře.
     */
    void vyberAkci();

    /**
     * Vypíše pravidla hry.
     */
    void vypisPravidla();

    /**
     * Zbourá libovolnou budovu na zadaném poli.
     * @param x - první souřadnice
     * @param y - druhá souřadnice
     */
    void zbouratBudovu(int x, int y);

    /**
     * Výběr budovy, která se bude stavět.
     */
    void vyberBudovu();

    /**
     * Vypisuje info o městě.
     */
    void infooMeste();

    /**
     * Zjistí, jestli je budova na zadaném poli u silnice.
     * @param x - první souřadnice
     * @param y - druhá souřadnice
     * @return Zda je u silnice.
     */
    bool jeUSilnice(int x, int y);

};