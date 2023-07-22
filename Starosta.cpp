//
// Created by Ondra on 15.11.2021.
//

#include "Starosta.h"

Starosta::Starosta(std::string jmeno) {
    m_jmeno = jmeno;
}

std::string Starosta::getJmeno() {
    return m_jmeno;
}