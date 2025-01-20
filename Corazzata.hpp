#pragma once
#include "Nave.hpp"

class Corazzata : public Nave
{
public:
    Corazzata() : Nave(4) {}
    //~Corazzata() override = default;

    std::string getNome() const override
    {
        return "Corazzata";
    }
};
