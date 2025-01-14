#include "Casella.hpp"

void SetColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

std::ostream& operator<<(std::ostream& os, const Casella& casella)
{
    switch (casella.stato.getStato())
    {
    case StatoCasella::Stato::acqua:
        SetColor(12);
        os << casella.coordinata_x << casella.coordinata_y << "(A)";
        break;
    case StatoCasella::Stato::occupata:
        os << casella.coordinata_x << casella.coordinata_y << "(N)";
        break;
    default:
        os << "Stato non valido";
        break;
    }
    SetColor(7);
    return os;
}