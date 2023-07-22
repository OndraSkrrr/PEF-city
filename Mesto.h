//
// Created by Uživatel on 10.11.2021.
//

#ifndef SEMESTRALKA_PEFCITY_MESTO_H
#define SEMESTRALKA_PEFCITY_MESTO_H

#include "iostream"
#include "array"
#include "Stavba.h"

/**
 * @authors xsmikmat, xskrob, xglas
 * @brief Kontejner pro manipulaci s městem.
 */
class Mesto {
private:
    std::string m_nazev;
    std::array<std::array<Stavba *, 20>, 20> mapa{};
    int m_pocetObyvatel;
    float m_spokojenost;
    int m_nezamestnost;
    //promenne potreba pro vypocet spokojenost
    /**
     * Toto pole zaznamenává počet jednotlivých druhů budov ve městě, přičemž index = ID budovy
     * a hodnota v poli na daném indexu odpovídá počtu budov onoho typu.
     */
    std::array<int, 11> m_budovyPocty;
public:
    Mesto(std::string nazev);

    ~Mesto();

    /**
     * Vyplní pole na [x,y] zadanou stavbou.
     * @param stavba
     * @param x
     * @param y
     */
    void vyplnPole(Stavba *stavba, int x, int y);

    /**
     * Vypíše mapu města na standardní výstup.
     */
    void zobrazMesto();

    /**
     * Spočítá přírůstek spokojenosti za určitou dobu, použití v setSpokojenost.
     * @return hodnota přírůstku
     */
    float spocitejPrirustekSpokojenosti();

    /**
     * Vrací druh budovy, která je na poli [x,y].
     * @param x
     * @param y
     * @return Pokud je budova, číslo druhu, jinak -1.
     */
    int druhBudovyNaPozici(int x, int y);

    /**
     * Vrací, zda je stavba na [x,y] u silnice.
     * @param x
     * @param y
     * @return Pokud je stavba u silnice - true, pokud není stavba nebo nestojí u silnice - false.
     */
    bool getUSilnice(int x,
                     int y);

    /**
     * Zvýší spokojenost obyvatel o přírůstek.
     * @param prirustek - výsledek z funkce spocitejPrirustekSpokojenosti
     */
    void setSpokojenost(float prirustek);

    /**
     * Dle m_budovyPocty určí počet pracovních míst
     * a počet obyvatel a vypočte nezaměstnanost, tu vloží do m_nezamestnanost.
     */
    void
    setNezamestnanost();

    /**
     * Podle počtu domů (v m_budovyPocty) vypočte počet obyvatel a vloží ho do m_pocetObyvatel.
     */
    void setPocetObyvatel();

    /**
     *
     * @return Spokojenost v %.
     */
    float getSpokojenost();

    /**
     * Zvýší počet budov daného druhu.
     * @param druh - druh budovy, kterou přičítáme
     */
    void setBudovu(int druh);

    /**
     *
     * @return Nezaměstnanost v %.
     */
    int getNezamestnanost();

    /**
     *
     * @return Počet obyvatel.
     */
    int getPocetObyvatel();

    /**
     *
     * @return Název města.
     */
    std::string getNazev();

    /**
     *
     * @return Počet budov všech druhů.
     */
    std::array<int, 11> getBudovyPocty();

    /**
     * Převádí čísla budov na textovou reprezentaci.
     * @param id - jakou budovu převádíme
     * @return Převedené jméno.
     */
    std::string prevedBudovu(int id);

    /**
     * Zneplatní všechny silnice.
     */
    void silniceOFF();

    /**
     * Rekurzivně zplatňuje silnice připojené k silnici na [x,y].
     * @param x
     * @param y
     */
    void silniceON(int x, int y);
};


#endif //SEMESTRALKA_PEFCITY_MESTO_H
