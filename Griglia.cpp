#include "Griglia.hpp"

Griglia::Griglia(std::pair<int, int> _dim, Giocatore _g)
{
	dim = _dim;
	g = _g;

    for (int i = 0; i < this->dim.first; i++)
    {
        for (int j = 0; j < this->dim.second; j++)
        {
			ListaCaselle[i][j] = Casella(i, 'A' + j, StatoCasella::acqua);
        }
    }
}

bool Griglia::ScegliPosizione(int x, char y, std::string direction, int dimNave)
{
    // Controlla se la nave può essere piazzata
    for (int i = 0; i < dimNave; i++)
    {
        if (direction == "H") // Orizzontale
        {
            // Controlla se esce dai limiti orizzontali
            if (x < 0 || x >= this->dim.first || y + i >= 'A' + this->dim.second)
                return false;

            // Controlla sulla riga in cui si vuole piazzare la nave
            if (FindCasella(x, y + i)->getStato() == StatoCasella::occupata)
                return false;

            // Controlla sulla riga superiore
            if (x > 0)
            {
                if (FindCasella(x - 1, y + i)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in alto a sinistra
                if (y + i > 'A' && FindCasella(x - 1, y + i - 1)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in alto a destra
                if (y + i < 'A' + this->dim.second - 1 && FindCasella(x - 1, y + i + 1)->getStato() == StatoCasella::occupata)
                    return false;
            }

            // Controlla sulla riga inferiore
            if (x < this->dim.first - 1)
            {
                if (FindCasella(x + 1, y + i)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in basso a sinistra
                if (y + i > 'A' && FindCasella(x + 1, y + i - 1)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in basso a destra
                if (y + i < 'A' + this->dim.second - 1 && FindCasella(x + 1, y + i + 1)->getStato() == StatoCasella::occupata)
                    return false;
            }
        }
        else if (direction == "V") // Verticale
        {
            // Controlla se esce dai limiti verticali
            if (x + i >= this->dim.first || y < 'A' || y >= 'A' + this->dim.second)
                return false;

            // Controlla sulla colonna in cui si vuole piazzare la nave
            if (FindCasella(x + i, y)->getStato() == StatoCasella::occupata)
                return false;

            // Controlla sulla colonna a sinistra
            if (y > 'A')
            {
                if (FindCasella(x + i, y - 1)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in alto a sinistra
                if (x + i > 0 && FindCasella(x + i - 1, y - 1)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in basso a sinistra
                if (x + i < this->dim.first - 1 && FindCasella(x + i + 1, y - 1)->getStato() == StatoCasella::occupata)
                    return false;
            }

            // Controlla sulla colonna a destra
            if (y < 'A' + this->dim.second - 1)
            {
                if (FindCasella(x + i, y + 1)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in alto a destra
                if (x + i > 0 && FindCasella(x + i - 1, y + 1)->getStato() == StatoCasella::occupata)
                    return false;

                // Controlla diagonale in basso a destra
                if (x + i < this->dim.first - 1 && FindCasella(x + i + 1, y + 1)->getStato() == StatoCasella::occupata)
                    return false;
            }
        }
    }

    return true; // Se nessuna condizione ha fallito, la posizione è valida
}

Casella *Griglia::FindCasella(int x, char y)
{
    for (int i = 0; i < this->dim.first; i++)
    {
        for (int j = 0; j < this->dim.second; j++)
        {
            if (ListaCaselle[i][j].getCoordinataX() == x && ListaCaselle[i][j].getCoordinataY() == y)
                return &ListaCaselle[i][j];
        }
    }
	return nullptr;
}

void Griglia::AggiornaGriglia()
{
	for (int i = 0; i < this->dim.first; i++)
	{
		for (int j = 0; j < this->dim.second; j++)
		{
			ListaCaselle[i][j].AggiornaGriglia();
		}
	}
}

