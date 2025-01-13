#pragma once

#include <iostream>
#include <string>

#include "Griglia.hpp"

class Turno
{
private:
    std::string nickGiocatore; // Identifica il giocatore usando il nickname
public:
    Turno(const std::string& _giocatore) : nickGiocatore(_giocatore) {}
    virtual ~Turno() {}

    virtual void CreateAttacco(int x, char y, Griglia* griglia, bool esito)  = 0; // Metodo virtuale puro per gestire l'attacco
    std::string getNickGiocatore() const { return nickGiocatore; } // Getter per il nickname del giocatore
};
