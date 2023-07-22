//
// Created by marek on 09.11.21.
//

#ifndef SEMESTRALKA_PEFCITY_STAVBA_H
#define SEMESTRALKA_PEFCITY_STAVBA_H

#include "iostream"
#include <string>

/**
 * @authors xsmikmat, xskrob, xglas
 * @brief Kontejner pro informace o stavbě.
 */
class Stavba {
private:
    int m_druh;
    int m_cena;
    bool m_uSilnice;
    std::string m_popis;
public:
    Stavba(int druh, bool uSilnice);

    /**
     *
     * @return Druh stavby.
     */
    int getDruh();

    /**
     *
     * @return Cena stavby.
     */
    int getCena();

    /**
     *
     * @return Jestli je stavba u silnice.
     */
    bool getUSilnice();

    /**
     * Mění, jestli je stavba u silnice.
     * @param uSilnice
     */
    void setUSilnice(bool uSilnice);

    /**
     *
     * @return Popis stavby.
     */
    std::string getPopis();

};


#endif //SEMESTRALKA_PEFCITY_STAVBA_H
