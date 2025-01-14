#include <iostream>
#include <time.h>

#include "BattagliaNavale.hpp"
#include "GiocatoreUmano.hpp"


int main()
{
    srand(time(0));
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
        gioco.Scegli_Impostazioni(false, std::make_pair(10, 10), 5, SecondPlayerNickname);
    }
    else
    {
        gioco.Scegli_Impostazioni(true, std::make_pair(10, 10), 5, SecondPlayerNickname);
    }

    gioco.ConfermaImpostazioni();

    Partita* partita = gioco.getPartitaCorrente();
    Giocatore* giocatore2 = partita->getGiocatore2();
    //controlla se il secondo giocatore è un bot o umano così da sapere come giocare il turno
    //gioco.IniziaTurnoSchieramento(mainPlayer, partita);
    int maxNumNavi = partita->GetNumeroNavi();
    int currNumNavi = maxNumNavi;

    std::vector<Giocatore*> giocatori = { giocatore2, mainPlayer };
    //std::unordered_map<std::string, int> mappaNavi = gioco.CreaMappaNavi();

    for(auto&giocatore : giocatori)
    {
        std::unordered_map<std::string, int> mappaNavi = gioco.CreaMappaNavi();
        gioco.IniziaTurnoSchieramento(giocatore, partita);
        while (currNumNavi > 0)
        {
            std::cout << "--------------------------------------------------------------" << std::endl;

            // Stampa la griglia del giocatore corrente
            partita->StampaGriglia(giocatore);

            // Itera attraverso la mappa e stampa il nome della nave e il numero disponibile
            std::cout << "Navi disponibili:" << std::endl;
            for (const auto& pair : mappaNavi)
            {
                const std::string& nome = pair.first;
                int numero = pair.second;            
                std::cout << nome << ": " << numero << " disponibili" << std::endl;
            }
            //aggiungere messaggio che comunica id delle navi
            std::cout << "Inserire id della nave che si vuole schierare" << std::endl;
            std::cout << "Incrociatore(id 1), Corazzata(id 2), Portaerei(id 3), Sottomarino(id 4)" << std::endl;

            // Chiedi all'utente di selezionare una nave
            // La logica di scelta della nave del bot va implementata anche in scegliNave
            // Oltre al successivo sorteggio delle posizioni su cui piazzare le navi
            int id;
            //se il turno e' del secondo giocatore ed e' un bot
            if (partita->get_TurnoCorrente()->getNickGiocatore() == giocatore2->getNickname() && partita->isG2_Umano() == false)
            {
                std::cout << "Il secondo giocatore e' un bot" << std::endl;
                id = rand() % 4 + 1;
            }
            else 
            {
                std::cin >> id;
            }
            if (!gioco.ScegliNave(id))
            {
                std::cout << "Errore nella selezione della nave. Riprova!" << std::endl;
                continue;
            }

            // Chiedi all'utente la posizione e la direzione per piazzare la nave
            // Se il secondoGiocatore e' un bot allora usa posizioni a caso

            int posizioneX;
            char posizioneY;
            std::string direction;

            if (partita->get_TurnoCorrente()->getNickGiocatore() == giocatore2->getNickname() && partita->isG2_Umano() == false)
            {
                posizioneX = rand() % partita->getDimGriglia().first;
                posizioneY = 'A'+(rand() % partita->getDimGriglia().second);
                int temp = rand() % 2;
                direction = temp == 0 ? "H" : "V";
            }
            else 
            {
                std::cout << "Scegli la posizione X: ";
                std::cin >> posizioneX;

                std::cout << "Scegli la posizione Y: ";
                std::cin >> posizioneY;

                std::cout << "Scegli la direzione (H/V): ";
                std::cin >> direction;
            }

            // Prova a piazzare la nave
            if (gioco.ScegliPosizione(posizioneX, std::toupper(posizioneY), direction))
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
        partita->ResetTurnoSchieramento();
        currNumNavi = maxNumNavi;
    }

    std::cout << "I giocatori hanno piazzato tutte le navi" << std::endl;
    //partita->StampaGriglieG1();

    //gioco.ScegliNave();
    return 0;
}
