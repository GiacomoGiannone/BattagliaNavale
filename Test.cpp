#ifdef TEST_MODE

#include <iostream>

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }
#define ASSERT_EQUAL(x,y) { if(x!=y) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;}
#define ASSERT_UNEQUAL(x,y) { if(x==y) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;}
#define ASSERT_NOT_NULL(x) { if ((x) == nullptr) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << ": pointer is null" << std::endl; }

#include "Griglia.hpp"
#include "Giocatore.hpp"
#include "BattagliaNavale.hpp"
#include "Partita.hpp"
#include "GiocatoreUmano.hpp"
#include "Bot.hpp"

#include <chrono>
#include <thread>
#include <unordered_map>
#include <cctype>
#include <cstdlib>

void ClearConsole()
{
#ifdef _WIN32
    system("cls"); //Windows
#else
    system("clear"); //Unix/Linux/macOS
#endif
}

//test della casella
void testCasella()
{
	Casella casella_1(5, 'A', StatoCasella::acqua);
	Casella casella_2(7, 'C', StatoCasella::occupata);
	Casella casella_3(1, 'F', StatoCasella::colpita);

	ASSERT_EQUAL(casella_1.getCoordinataX(), 5);
	ASSERT_EQUAL(casella_1.getCoordinataY(), 'A');

	ASSERT_EQUAL(casella_2.getCoordinataX(), 7);
	ASSERT_EQUAL(casella_2.getCoordinataY(), 'C');

	ASSERT_EQUAL(casella_3.getCoordinataX(), 1);
	ASSERT_EQUAL(casella_3.getCoordinataY(), 'F');
}

//test del giocatore
void testGiocatore()
{
	Giocatore* g1 = new Giocatore("G1");
	Giocatore* g2 = new Giocatore("G2");
	Giocatore* g3 = new Giocatore("G3");

	ASSERT_EQUAL(g1->getNickname(), "G1");
	ASSERT_EQUAL(g2->getNickname(), "G2");
	ASSERT_EQUAL(g3->getNickname(), "G3");

    delete g1, g2, g3;
}

//test della Griglia
void testGriglia()
{
    Giocatore* g1 = new Giocatore("G1");
    Giocatore* g2 = new Giocatore("G2");
    Giocatore* g3 = new Giocatore("G3");

    Griglia griglia_1(std::make_pair(10, 10), g1);
    Griglia griglia_2(std::make_pair(15, 15), g2);
    Griglia griglia_3(std::make_pair(12, 12), g3);

    ASSERT_EQUAL(griglia_1.getGiocatore()->getNickname(), "G1");
    ASSERT_EQUAL(griglia_2.getGiocatore()->getNickname(), "G2");
    ASSERT_EQUAL(griglia_3.getGiocatore()->getNickname(), "G3");

    ASSERT_EQUAL(griglia_1.getDim(), std::make_pair(10, 10));
    ASSERT_EQUAL(griglia_2.getDim(), std::make_pair(15, 15));
    ASSERT_EQUAL(griglia_3.getDim(), std::make_pair(12, 12));

    griglia_1.CreateAttacco(5, 'C', true);
    griglia_1.CreateAttacco(3, 'A', false);

    Attacco* attacco1 = griglia_1.getAttacco(5, 'C');
    ASSERT_EQUAL(attacco1->getCoordinataX(), 5);
    ASSERT_EQUAL(attacco1->getCoordinataY(), 'C');
    ASSERT_EQUAL(attacco1->getEsito(), true);

    Attacco* attacco2 = griglia_1.getAttacco(3, 'A');
    ASSERT_EQUAL(attacco2->getCoordinataX(), 3);
    ASSERT_EQUAL(attacco2->getCoordinataY(), 'A');
    ASSERT_EQUAL(attacco2->getEsito(), false);

    try 
    {
        griglia_1.FindCasella(20, 'Z');
        griglia_2.FindCasella(17, 'K');
        griglia_3.FindCasella(34, 'M');
        IS_TRUE(false);
    }
    catch (std::out_of_range&) 
    {
        IS_TRUE(true);
    }

    delete g1, g2, g3;
    delete attacco1, attacco2;
}

//Test di battagliaNavale
void testBattagliaNavale()
{
    Nave* incrociatore = new Incrociatore();
    Nave* portaerei = new Portaerei();
    Nave* sottomarino = new Sottomarino();
    Nave* corazzata = new Corazzata();

    BattagliaNavale* bn = BattagliaNavale::getInstance();
    
    bn->ScegliNave(1);
    ASSERT_EQUAL(bn->getNave()->getNome(), incrociatore->getNome());
    
    bn->ScegliNave(2);
    ASSERT_EQUAL(bn->getNave()->getNome(), corazzata->getNome());

    bn->ScegliNave(3);
    ASSERT_EQUAL(bn->getNave()->getNome(), portaerei->getNome());

    bn->ScegliNave(4);
    ASSERT_EQUAL(bn->getNave()->getNome(), sottomarino->getNome());

    ASSERT_EQUAL(bn->ScegliNave(5), false);

    ASSERT_EQUAL(bn->getNave()->getNome(), sottomarino->getNome());

    delete incrociatore, portaerei, sottomarino, corazzata;
}

//Test di partita
void testPartita()
{
    Giocatore* g1 = new Giocatore("G1");
    Giocatore* g2 = new Giocatore("G2");

    Partita* partita = new Partita(g1);

    partita->creaTurno(g1);
    ASSERT_EQUAL(partita->get_TurnoCorrente()->getNickGiocatore(), g1->getNickname());
    partita->ResetTurnoSchieramento();
    ASSERT_EQUAL(partita->getLastValidTurnoSchieramento()->getNickGiocatore(), g1->getNickname());

    partita->creaTurno(g2);
    ASSERT_EQUAL(partita->get_TurnoCorrente()->getNickGiocatore(), g2->getNickname());
    partita->ResetTurnoSchieramento();
    ASSERT_EQUAL(partita->getLastValidTurnoSchieramento()->getNickGiocatore(), g2->getNickname());

    partita->CreaImpostazioni(false, std::make_pair(15, 15), 10, g2->getNickname());
    
    ASSERT_UNEQUAL(partita->getGriglia(g1), nullptr);
    ASSERT_UNEQUAL(partita->getGriglia(g2), nullptr);

    ASSERT_EQUAL(partita->getGriglia(g1)->getDim(), std::make_pair(15, 15));
    ASSERT_EQUAL(partita->getGriglia(g2)->getDim(), std::make_pair(15, 15));

    ASSERT_EQUAL(partita->isG2_Umano(), false);
    ASSERT_EQUAL(partita->GetNumeroNavi(), 10);

    delete g1;
    delete g2;
}

void testPartitaCompleta() 
{
    srand(time(0));

    BattagliaNavale* gioco = BattagliaNavale::getInstance();
    std::string MainPlayerNickname = "TestPlayer";
    std::cout << "Benvenuto, " << MainPlayerNickname << "!" << std::endl;

    Giocatore* mainPlayer = new GiocatoreUmano(MainPlayerNickname);

    gioco->IniziaNuovaPartita(mainPlayer);

    std::string SecondPlayerNickname = "BotPlayer";

    int numNavi = 5;
    int dimGriglia = 10;
    gioco->Scegli_Impostazioni(false, std::make_pair(dimGriglia, dimGriglia), numNavi, SecondPlayerNickname);

    Partita* partita = gioco->getPartitaCorrente();
    ASSERT_NOT_NULL(partita);
    Giocatore* giocatore2 = partita->getGiocatore2();
    ASSERT_NOT_NULL(giocatore2);

    int maxNumNavi = partita->GetNumeroNavi();
    for (Giocatore* giocatore : { mainPlayer, giocatore2 }) 
    {
        std::unordered_map<std::string, int> mappaNavi = gioco->CreaMappaNavi();
        gioco->IniziaTurnoSchieramento(giocatore, partita);

        int currNumNavi = maxNumNavi;
        int tentativi = 0;
        while (currNumNavi > 0)
        {
            tentativi++;
            int id = rand() % 4 + 1; 
            if (!gioco->ScegliNave(id)) 
            {
                continue;
            }
            int posizioneX = rand() % dimGriglia;
            char posizioneY = 'A' + (rand() % dimGriglia);
            std::string direction = (rand() % 2 == 0) ? "H" : "V";

            Nave* naveSelezionata = gioco->getNave();
            if (naveSelezionata && mappaNavi[naveSelezionata->getNome()] > 0 && gioco->ScegliPosizione(posizioneX, std::toupper(posizioneY), direction)) 
            {
                mappaNavi[naveSelezionata->getNome()]--;
                currNumNavi--;
                std::cout << "Nave " << naveSelezionata->getNome() << " piazzata correttamente!" << std::endl;
            }
            else 
            {
                std::cout << "Errore nel posizionamento (tentativo " << tentativi << ")." << std::endl;
            }
        }
        partita->StampaGriglia(giocatore);
        std::cout << std::endl;
        partita->ResetTurnoSchieramento();
    }

    std::cout << "I giocatori hanno piazzato tutte le navi" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ClearConsole();

    std::cout << "Inizia la fase di attacco!" << std::endl;
    while (!partita->isOver()) 
    {
        Giocatore* giocatoreCorrente = nullptr;
        Turno* ultimoTurnoAttacco = partita->getLastValidTurnoAttacco();
        if (ultimoTurnoAttacco == nullptr || ultimoTurnoAttacco->getNickGiocatore() == giocatore2->getNickname()) 
        {
            giocatoreCorrente = mainPlayer;
        }
        else 
        {
            giocatoreCorrente = giocatore2;
        }
        std::cout << "Turno del giocatore " << giocatoreCorrente->getNickname() << std::endl;
        partita->getGriglia(giocatoreCorrente)->StampaGriglia();
        std::cout << "Griglia degli attacchi:" << std::endl;
        Giocatore* avversario = (giocatoreCorrente == mainPlayer) ? giocatore2 : mainPlayer;
        partita->getGriglia(avversario)->DrawAttackGrid();

        int posizioneX = rand() % dimGriglia;
        char posizioneY = 'A' + (rand() % dimGriglia);
        std::cout << "Attacco alle coordinate: " << posizioneX << ", " << posizioneY << std::endl;
        gioco->ScegliPosizioneAttacco(posizioneX, posizioneY);
        ClearConsole();
    }

    IS_TRUE(partita->isOver());
    Giocatore* vincitore = partita->getWinner();
    ASSERT_NOT_NULL(vincitore);
    std::cout << "Partita finita, vincitore: " << vincitore->getNickname() << std::endl;

    delete partita;
    delete mainPlayer;
    delete giocatore2;
}

int main()
{
	testCasella();
	testGiocatore();
	testGriglia();
    testBattagliaNavale();
    testPartita();
    testPartitaCompleta();
}

#endif