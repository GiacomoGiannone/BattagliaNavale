#ifdef TEST_MODE

#include <iostream>

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }
#define ASSERT_EQUAL(x,y) { if(x!=y) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;}
#define ASSERT_UNEQUAL(x,y) { if(x==y) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;}

#include "Griglia.hpp"
#include "Giocatore.hpp"
#include "BattagliaNavale.hpp"
#include "Partita.hpp"

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
}

int main()
{
	testCasella();
	testGiocatore();
	testGriglia();
    testBattagliaNavale();
    testPartita();
}

#endif