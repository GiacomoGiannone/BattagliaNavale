#pragma once
#include "Nave.hpp"

class Corazzata : public Nave
{
public:
    Corazzata() : Nave(4) {} // Inizializza la dimensione nel costruttore base
    ~Corazzata() override = default; // Distruttore di default

    std::string getNome() const override // Implementazione del metodo puro
    {
        return "Corazzata";
    }
};
