#pragma once

#include <iostream>
#include <vector>
#include "Turno.hpp"
#include "Attacco.hpp"

class TurnoAttacco : public Turno
{
private:
    std::vector<Attacco> Lista_Attacchi; // Lista degli attacchi effettuati
public:
    // Costruttore che utilizza il nickname del giocatore
    TurnoAttacco(const std::string& _nickGiocatore) : Turno(_nickGiocatore) {}
    ~TurnoAttacco() {}

    void CreateAttacco(int x, char y) const override
    {
        std::cout << "Creazione attacco alle coordinate: " << x << ", " << y << std::endl;
    }
};
