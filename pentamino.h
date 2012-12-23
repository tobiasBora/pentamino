#ifndef PENTAMINO_H
#define PENTAMINO_H

#include "plateau.h"

class Pentamino
{
public:
    Pentamino();
    void lancer();

protected:
    int test;
    Plateau *plateau;
};

#endif
