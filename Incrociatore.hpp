#pragma once
#include "Nave.hpp"

class Incrociatore : public Nave
{
public:
    Incrociatore() : Nave(2) {} // Inizializza la dimensione nel costruttore base
    ~Incrociatore() override = default;

    std::string getNome() const override
    {
        return "Incrociatore";
    }
};
