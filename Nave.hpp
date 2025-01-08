#pragma once
#include <string>

class Nave
{
protected:
    int dimensione; 
public:
    Nave(int _dimensione) : dimensione(_dimensione) {} 
    virtual ~Nave() = default;

    virtual int getDimensione() const { return dimensione; } 
    virtual std::string getNome() const = 0;
};
