#include "Casella.hpp"

std::ostream& operator<<(std::ostream& os, const Casella& casella)
{
    switch (casella.stato.getStato())
    {
    case StatoCasella::Stato::acqua:
        os << "\033[34m"; // Blu
        os << casella.coordinata_x << casella.coordinata_y << "(A)";
        break;
    case StatoCasella::Stato::occupata:
        os << "\033[33m"; // Giallo
        os << casella.coordinata_x << casella.coordinata_y << "(N)";
        break;
    case StatoCasella::Stato::colpita:
        os << "\033[31m"; // Rosso
        os << "(X)";
        break;
    default:
        os << "\033[0m";
        os << "Stato non valido";
        break;
    }
    os << "\033[0m"; //restta il colore da un'iterazione all'altra per stampare i messaggi normali
    return os;
}

bool operator==(const Casella& lhs, const Casella& rhs) 
{
    return lhs.coordinata_x == rhs.coordinata_x && lhs.coordinata_y == rhs.coordinata_y && lhs.stato == rhs.stato;
}
