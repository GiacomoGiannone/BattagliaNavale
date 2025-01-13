#include "Casella.hpp"

std::ostream& operator<<(std::ostream& os, const Casella& casella)
{
    switch (casella.stato.getStato())
    {
    case StatoCasella::Stato::acqua:
        os << "Acqua";
        break;
    case StatoCasella::Stato::occupata:
        os << "Occupata";
        break;
    default:
        os << "Stato non valido";
        break;
    }
    return os;
}