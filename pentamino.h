#ifndef PENTAMINO_H
#define PENTAMINO_H

#include "plateau.h"
#include <vector>

class Pentamino
{
public:
    Pentamino();
    void lancer();
    Plateau *remplirRecur(Plateau *plateau, std::vector< Piece* > *pieces, int niveau=1, std::string chaine = "");
protected:
    int test;
    Plateau *plateau;
};

#endif
