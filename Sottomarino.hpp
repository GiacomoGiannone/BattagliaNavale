#pragma once
#include "Nave.hpp"

class Sottomarino : public Nave
{
public:
    Sottomarino() : Nave(3) {}
    ~Sottomarino() override = default;

    std::string getNome() const override
    {
        return "Sottomarino";
    }
};
