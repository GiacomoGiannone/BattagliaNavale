#include "Casella.hpp"

std::ostream& operator<<(std::ostream& os, const Casella& casella)
{
    switch (casella.stato.getStato())
    {
    case StatoCasella::Stato::acqua:
        os << casella.coordinata_x << casella.coordinata_y;
        break;
    case StatoCasella::Stato::occupata:
        os << casella.coordinata_x << casella.coordinata_y;
        break;
    default:
        os << "Stato non valido";
        break;
    }
    return os;
}