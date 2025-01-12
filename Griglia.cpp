#include "Griglia.hpp"
#include "Casella.hpp"
#include "Giocatore.hpp"

Griglia::Griglia(std::pair<int, int> _dim, Giocatore* _g)
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

std::vector<Casella*> Griglia::ScegliPosizione(int x, char y, std::string direction, int dimNave)
{
    std::vector<Casella*> caselleScelte;

    for (int i = 0; i < dimNave; i++)
    {
        if (direction == "H") // Orizzontale
        {
            // Controlla se esce dai limiti orizzontali
            if (x < 0 || x >= this->dim.first || y + i >= 'A' + this->dim.second)
                return {}; // Restituisce una lista vuota in caso di errore

            Casella* casella = FindCasella(x, y + i);
            if (casella->getStato() == StatoCasella::occupata)
                return {}; // Lista vuota

            // Controlla sulla riga superiore
            if (x > 0)
            {
                if (FindCasella(x - 1, y + i)->getStato() == StatoCasella::occupata)
                    return {};

                if (y + i > 'A' && FindCasella(x - 1, y + i - 1)->getStato() == StatoCasella::occupata)
                    return {};

                if (y + i < 'A' + this->dim.second - 1 && FindCasella(x - 1, y + i + 1)->getStato() == StatoCasella::occupata)
                    return {};
            }

            // Controlla sulla riga inferiore
            if (x < this->dim.first - 1)
            {
                if (FindCasella(x + 1, y + i)->getStato() == StatoCasella::occupata)
                    return {};

                if (y + i > 'A' && FindCasella(x + 1, y + i - 1)->getStato() == StatoCasella::occupata)
                    return {};

                if (y + i < 'A' + this->dim.second - 1 && FindCasella(x + 1, y + i + 1)->getStato() == StatoCasella::occupata)
                    return {};
            }

            caselleScelte.push_back(casella);
        }
        else if (direction == "V") // Verticale
        {
            // Controlla se esce dai limiti verticali
            if (x + i >= this->dim.first || y < 'A' || y >= 'A' + this->dim.second)
                return {};

            Casella* casella = FindCasella(x + i, y);
            if (casella->getStato() == StatoCasella::occupata)
                return {};

            // Controlla sulla colonna a sinistra
            if (y > 'A')
            {
                if (FindCasella(x + i, y - 1)->getStato() == StatoCasella::occupata)
                    return {};

                if (x + i > 0 && FindCasella(x + i - 1, y - 1)->getStato() == StatoCasella::occupata)
                    return {};

                if (x + i < this->dim.first - 1 && FindCasella(x + i + 1, y - 1)->getStato() == StatoCasella::occupata)
                    return {};
            }

            // Controlla sulla colonna a destra
            if (y < 'A' + this->dim.second - 1)
            {
                if (FindCasella(x + i, y + 1)->getStato() == StatoCasella::occupata)
                    return {};

                if (x + i > 0 && FindCasella(x + i - 1, y + 1)->getStato() == StatoCasella::occupata)
                    return {};

                if (x + i < this->dim.first - 1 && FindCasella(x + i + 1, y + 1)->getStato() == StatoCasella::occupata)
                    return {};
            }

            caselleScelte.push_back(casella);
        }
    }

    return caselleScelte; // Restituisce la lista delle caselle selezionate
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

void Griglia::CreateAttacco(int x, char y, bool esito)
{
	Attacco attacco = Attacco(x, y, esito);
	ListaAttacchi.push_back(attacco);
}

Giocatore* Griglia::getGiocatore()
{
	return g;
}