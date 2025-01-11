#pragma once

#include <iostream>

class StatoCasella
{
public:
    enum Stato { acqua, occupata };
private:
    Stato stato;
public:
    StatoCasella(Stato _stato = acqua) : stato(_stato) {}
    ~StatoCasella() {}

    Stato getStato() const { return stato; }

    bool operator==(const StatoCasella& sc) const
    {
        return stato == sc.stato;
    }

    bool operator==(Stato s) const
    {
        return stato == s;
    }
};
