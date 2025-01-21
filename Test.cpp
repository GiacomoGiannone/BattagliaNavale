#ifdef TEST_MODE

#include <iostream>

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }
#define ASSERT_EQUAL(x,y) { if(x!=y) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;}

#include "Griglia.hpp"
#include "Giocatore.hpp"

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

int main()
{
	testCasella();
	testGiocatore();
	testGriglia();
}

#endif