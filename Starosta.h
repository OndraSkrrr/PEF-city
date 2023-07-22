//
// Created by Ondra on 15.11.2021.
//

#ifndef SEMESTRALKA_PEFCITY_STAROSTA_H
#define SEMESTRALKA_PEFCITY_STAROSTA_H

#include <string>

/**
 * @authors xsmikmat, xskrob, xglas
 * @brief Kontejner pro informace o starostovi.
 */
class Starosta {
    std::string m_jmeno;
public:
    Starosta(std::string jmeno);

    /**
     *
     * @return Jméno starosty.
     */
    std::string getJmeno();
};


#endif //SEMESTRALKA_PEFCITY_STAROSTA_H
