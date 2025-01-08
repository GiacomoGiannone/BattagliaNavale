#pragma once
#include "Nave.hpp"

class Portaerei : public Nave
{
public:
    Portaerei() : Nave(5) {} // Dimensione della Portaerei
    ~Portaerei() override = default;

    std::string getNome() const override
    {
        return "Portaerei";
    }
};
