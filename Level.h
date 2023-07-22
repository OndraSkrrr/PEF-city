//
// Created by Ondra on 24.11.2021.
//

#ifndef SEMESTRALKA_PEFCITY_LEVEL_H
#define SEMESTRALKA_PEFCITY_LEVEL_H

#include <array>

/**
 * @authors xsmikmat, xskrob, xglas
 * @brief Kontejner pro informace o levelech.
 */
class Level {
    std::array<std::array<int, 11>, 11> m_lvlReq;
public:
    /**
     * Vygeneruje požadavky na jednotlivé levely (vygeneruje m_lvlReq matici).
     * @param hardness - obtížnost
     */
    Level(int hardness);

    /**
     * Výpis pro ověření, zda funguje (jinak nepoužívat).
     */
    void vypis();

    /**
     * Pokud je první vektor na každé pozici vetší nebo roven druhému vektoru, vráti true, jinak false.
     * @param vekt1 - první vektor
     * @param vekt2 - druhý vektor
     * @return - Je první vektor větší nebo roven.
     */
    bool arrayCompare(std::array<int, 11> vekt1,
                      std::array<int, 11> vekt2);

    /**
     * Vrátí level, na který pro zadaný vektor (počty jednotlivých budov) hráč dosáhne.
     * @param myCity - počty budov ve městě
     * @return Hodnota dosaženého levelu.
     */
    int dosazenyLvl(
            std::array<int, 11> myCity);
};


#endif //SEMESTRALKA_PEFCITY_LEVEL_H
