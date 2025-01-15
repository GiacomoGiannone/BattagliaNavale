#include "Griglia.hpp"
#include "Casella.hpp"
#include "Giocatore.hpp"

Griglia::Griglia(std::pair<int, int> _dim, Giocatore* _g)
{
    dim = _dim;
    g = _g;

    ListaCaselle.resize(dim.first);

    for (int i = 0; i < dim.first; i++)
    {
        ListaCaselle[i].resize(dim.second);
        for (int j = 0; j < dim.second; j++)
        {
            ListaCaselle[i][j] = new Casella(i, 'A' + j, StatoCasella::acqua);
        }
    }
}

std::vector<Casella*> Griglia::ScegliPosizione(int x, char y, std::string direction, int dimNave)
{
	std::cout << "Metodo ScegliPosizione Griglia" << std::endl;
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

Casella* Griglia::FindCasella(int x, char y)
{
    // Controlla che X e Y siano validi
    if (x < 0 || x >= dim.first)
    {
        throw std::out_of_range("Coordinate X fuori dai limiti");
    }
    if (y < 'A' || y >= 'A' + dim.second)
    {
        throw std::out_of_range("Coordinate Y fuori dai limiti");
    }

    int col = y - 'A';

    if (!ListaCaselle[x][col])
    {
        throw std::runtime_error("Casella non valida o non inizializzata");
    }

    return ListaCaselle[x][col];
}

void Griglia::AggiornaGriglia()
{
	for (int i = 0; i < this->dim.first; i++)
	{
		for (int j = 0; j < this->dim.second; j++)
		{
			ListaCaselle[i][j]->AggiornaGriglia();
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

void Griglia::StampaGriglia()
{
    if (ListaCaselle.empty()) {
        std::cerr << "Errore: ListaCaselle è vuota!" << std::endl;
        return;
    }

    for (int i = 0; i < this->dim.first; i++)
    {
        if (ListaCaselle[i].empty()) {
            std::cerr << "Errore: La riga " << i << " è vuota!" << std::endl;
            continue;
        }

        for (int j = 0; j < this->dim.second; j++)
        {
            std::cout << *ListaCaselle[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Griglia::isOver()
{
    for (int i = 0; i < ListaCaselle.size(); i++)
    {
        for (int j = 0; j < ListaCaselle.size(); j++)
        {
            if (ListaCaselle[i][j]->getStato() == StatoCasella::occupata)
            {
                return false;
            }
        }
    }
    return true;
}