#include "pentamino.h"
#include <iostream>
#include <stdlib.h>
#include "plateau.h"
#include "piece.h"
#include <vector>

using namespace std;

Pentamino::Pentamino()
{
     cout << "Création de l'instance de pentamino " << endl;

     /*
       aabbb
       aaabb

      */
     // Version qui fonctionne :
     // Création du plateau
     Plateau *plateau2 = new Plateau();
     cout << "--- Plateau vide ---" << endl;
     plateau2->setPlateau("plateau2.txt");
     plateau2->afficher();
         

     // Création des pièces
     vector< Piece* > *tableauPieces = new vector< Piece* >;  //Un tableau de 3 entiers valant tous 2



     Piece *piece2 = new Piece();
     piece2->setPieceString("bbb\n0bb\n");
     piece2->afficher();
     tableauPieces->push_back( piece2 );

     Piece *piece1 = new Piece();
     piece1->setPieceString("aa\naaa\n");
     tableauPieces->push_back( piece1 );
     piece1->afficher();

     cout << "On lance la récurrence" << endl;
     
     Plateau *plateauFinal = remplirRecur(plateau2, tableauPieces);
     if(plateauFinal)
     {
	  cout << "Une solution a été trouvée :" << endl;
	  plateauFinal->afficher();
     }
     else
     {
	  cout << "Aucune solution n'a été trouvée." << endl;
     }
     // plateauFinal->afficher();
     // cout << "--- piece1 ---" << endl;
     // piece1->afficher();

     
/*
     // Création du plateau
     plateau = new Plateau();
     plateau->setPlateau("plateau1.txt");
     cout << "--- Plateau vide ---" << endl;
     plateau->afficher();
         

     // Création des pièces
     Piece *piece1 = new Piece();
     piece1->setPieceString("aa\naa\naa");
     cout << "--- piece1 ---" << endl;
     piece1->afficher();

     // On insère la piece :
     cout << "--- Après ajout de la pièce ---" << endl;
     if(plateau->addPiece(piece1, 0, 0) < 0)
	  cout << "Pas possible !!!" << endl;
     plateau->afficher();
     int* array = plateau->searchFirstEmptyCase();
     cout << "La première case vide est " << array[0] << ", " << array[1] << endl;
*/
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

Plateau *Pentamino::remplirRecur(Plateau *plateau, vector< Piece* > *pieces)
{
     cout << "On reccur !" << endl;
     // On cherche la première case vide
     int *array = plateau->searchFirstEmptyCase();
     // Si il n'y en a pas, on a remplit tout le tableau, c'est gagné
     if(array[1] == -1)
	  return plateau;
     // Sinon on rajoute une nouvelle piece :
     Plateau *plateauCopy = 0;
     int retourAjout = -1;
     Plateau *retourPlateau = 0;
     // vector< Piece* > *pieces_del = new vector< Piece* >;
     // On parcours toutes les lettres
     for(unsigned int i=0; i < pieces->size(); i++)
     {
	  cout << "Piece nb " << i << " sur " << pieces->size() << endl;
	  pieces->at(i)->afficher();
	  // On essaye d'ajouter cette pièce
	  plateau->afficher();
	  cout << "on modif" << endl;
	  plateauCopy = new Plateau( *plateau);
	  retourAjout = plateauCopy->addPiece(pieces->at(i), array[0], array[1]);
	  plateau->afficher();
	  plateauCopy->afficher();
	  if(retourAjout > 0)
	  {
	       // Si ça fonctionne on envoie à la fonction courrante le nouveau tableau et les nouvelles pièces (penser à enlever la pièce courante)
	       // pieces_del = pieces;
	       vector< Piece* > pieces_del(*pieces);
	       pieces_del.erase(pieces_del.begin()+i);
	       retourPlateau = remplirRecur(plateauCopy, &pieces_del);
	       // Si la fonction retourne un tableau plein, on le retourne
	       // (on a gagné)
	       if(retourPlateau)
	       {
		    retourPlateau->afficher();
		    return retourPlateau;
	       }


	  }
	 
     }
     // Si on fini la boucle, on n'a rien trouvé : perdu
     return 0;
}
