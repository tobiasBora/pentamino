#include "pentamino.h"
#include <iostream>
#include <stdlib.h>
#include "plateau.h"
#include "piece.h"

using namespace std;

Pentamino::Pentamino()
{
     cout << "Création de l'instance de pentamino" << endl;

     // Création du plateau
     plateau = new Plateau();
     plateau->setPlateau("plateau1.txt");
     cout << "--- Plateau vide ---" << endl;
     plateau->afficher();
         

     // Création des pièces
     Piece *piece1 = new Piece();
     piece1->setPieceString("aa\naa\n");
     cout << "--- piece1 ---" << endl;
     piece1->afficher();

     // On insère la piece :
     cout << "--- Après ajout de la pièce ---" << endl;
     if(plateau->addPiece(piece1, 4, 9) < 0)
	  cout << "Pas possible !!!" << endl;
     plateau->afficher();
     
     // Exemples applications :
/*   // Création du plateau
     plateau = new Plateau();
     cout << "- 1er version d'initialiation" << endl;
     plateau->setPlateau("plateau1.txt");
     plateau->afficher();
     cout << "  On converti en chaine :" << endl;
     cout << plateau->toString();
     cout << "- 2e version d'initialisation" << endl;
     plateau->setPlateauString("11111\n111111\n11011\n11111\n11111\n1111111");
     plateau->afficher();
*/
     
     
}
/*
void Pentamino::setPlateau(string file)
{
        
}*/

void Pentamino::lancer()
{
     cout << "C'est parti !";

}
