#include "pentamino.h"
#include <iostream>
#include <stdlib.h>
#include "plateau.h"

using namespace std;

Pentamino::Pentamino()
{
     cout << "Création de l'instance de pentamino" << endl;

     // Création du plateau
     plateau = new Plateau();
     cout << "- 1er version d'initialiation" << endl;
     plateau->setPlateau("plateau1.txt");
     plateau->afficher();
     cout << "  On converti en chaine :" << endl;
     cout << plateau->toString();
     cout << "- 2e version d'initialisation" << endl;
     plateau->setPlateauString("11111\n111111\n11011\n11111\n11111\n1111111");
     plateau->afficher();     
     // Création des pièces
     
}
/*
void Pentamino::setPlateau(string file)
{
        
}*/

void Pentamino::lancer()
{
     cout << "C'est parti !";

}
