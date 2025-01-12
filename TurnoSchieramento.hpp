#pragma once

#include <iostream>
#include "Turno.hpp"

class TurnoSchieramento : public Turno
{
public:
    // Costruttore che utilizza il nickname del giocatore
    TurnoSchieramento(const std::string& _nickGiocatore) : Turno(_nickGiocatore) {}
    ~TurnoSchieramento() {}

    void CreateAttacco(int x, char y, Griglia griglia, bool esito)
    {
        std::cout << "TurnoSchieramento non gestisce attacchi." << std::endl;
    }
};
