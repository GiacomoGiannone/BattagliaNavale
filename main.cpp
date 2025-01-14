#include <iostream>

#include "BattagliaNavale.hpp"
#include "GiocatoreUmano.hpp"


int main()
{
    BattagliaNavale gioco;
	
    std::cout << "Benvenuto in Battaglia Navale!" << std::endl;
    std::cout << "Inserisci il tuo nickname: ";
	std::string MainPlayerNickname;
	std::cin >> MainPlayerNickname;
	std::cout << "Benvenuto " << MainPlayerNickname << "!" << std::endl;
    
	Giocatore* mainPlayer = new GiocatoreUmano(MainPlayerNickname);

	gioco.IniziaNuovaPartita(mainPlayer);

	std::cout << "Inserisci il nickname del tuo avversario: ";
	std::string SecondPlayerNickname;
	std::cin >> SecondPlayerNickname;
	std::cout << "Benvenuto " << SecondPlayerNickname << "!" << std::endl;
	std::cout << "Il secondo giocatore è un bot? (Y/N): ";
	char isBot;
	std::cin >> isBot;

	std::cout << "Impostazioni di default: griglia 10x10, 5 navi" << std::endl;

	if (isBot == 'Y' || isBot == 'y')
	{
		gioco.Scegli_Impostazioni(true, std::make_pair(10, 10), 5, SecondPlayerNickname);
	}
	else
	{
		gioco.Scegli_Impostazioni(false, std::make_pair(10, 10), 5, SecondPlayerNickname);
	}

	gioco.ConfermaImpostazioni();

	Partita* partita = gioco.getPartitaCorrente();
	Giocatore* giocatore2 = partita->getGiocatore2();
	//controlla se il secondo giocatore è un bot o umano così da sapere come giocare il turno
	gioco.IniziaTurnoSchieramento(mainPlayer, partita);
	int maxNumNavi = partita->GetNumeroNavi();
	int currNumNavi = maxNumNavi;

	std::unordered_map<std::string, int> mappaNavi = gioco.CreaMappaNavi();

    while (currNumNavi > 0)
    {
        std::cout << "--------------------------------------------------------------" << std::endl;

        // Stampa la griglia del giocatore 1
        partita->StampaGriglieG1();

        // Itera attraverso la mappa e stampa il nome della nave e il numero disponibile
        std::cout << "Navi disponibili:" << std::endl;
        for (const auto& pair : mappaNavi)
        {
            const std::string& nome = pair.first;  // Accesso alla chiave
            int numero = pair.second;             // Accesso al valore
            std::cout << nome << ": " << numero << " disponibili" << std::endl;
        }

        // Chiedi all'utente di selezionare una nave
        if (!gioco.ScegliNave())
        {
            std::cout << "Errore nella selezione della nave. Riprova!" << std::endl;
            continue;
        }

        // Chiedi all'utente la posizione e la direzione per piazzare la nave
        int posizioneX;
        char posizioneY;
        std::string direction;

        std::cout << "Scegli la posizione X: ";
        std::cin >> posizioneX;

        std::cout << "Scegli la posizione Y: ";
        std::cin >> posizioneY;

        std::cout << "Scegli la direzione (H/V): ";
        std::cin >> direction;

        // Prova a piazzare la nave
        if (gioco.ScegliPosizione(posizioneX, posizioneY, direction))
        {
            // Recupera la nave selezionata e aggiorna il conteggio nella mappa
            Nave* naveSelezionata = gioco.getNave();
            if (naveSelezionata)
            {
                std::string nomeNave = naveSelezionata->getNome();
                if (mappaNavi[nomeNave] > 0)
                {
                    mappaNavi[nomeNave]--; // Decrementa il numero di navi disponibili di quel tipo
                    currNumNavi--;         // Decrementa il numero totale di navi da piazzare
                    std::cout << "Nave " << nomeNave << " piazzata correttamente!" << std::endl;
                }
                else
                {
                    std::cout << "Errore: nessuna nave di tipo " << nomeNave << " disponibile per il piazzamento!" << std::endl;
                }
            }
            else
            {
                std::cout << "Errore: nessuna nave selezionata!" << std::endl;
            }
        }
        else
        {
            std::cout << "Errore: posizione non valida. Riprova!" << std::endl;
        }
    }


	//partita->StampaGriglieG1();

    //gioco.ScegliNave();
    return 0;
}
