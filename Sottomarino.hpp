#pragma once
#include "Nave.hpp"

class Sottomarino : public Nave
{
public:
    Sottomarino() : Nave(3) {} // Dimensione del Sottomarino
    ~Sottomarino() override = default;

    std::string getNome() const override
    {
        return "Sottomarino";
    }
};
