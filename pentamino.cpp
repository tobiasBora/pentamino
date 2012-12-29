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



     /********* Cette version résoud celui ci : ***************
     
     // aabbb
     // aaabb

      
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
     *******************/


     /* Version plus compliquée :
      */

     Plateau *plateau2 = new Plateau();
     cout << "--- Plateau vide ---" << endl;
     plateau2->setPlateau("plateau3.txt");
     plateau2->afficher();
         

     // Création des pièces
     vector< Piece* > *tableauPieces = new vector< Piece* >;  //Un tableau de 3 entiers valant tous 2


     // Piece *piece1 = new Piece();
     // piece1->setPieceString("010\n010\n");
     tableauPieces->push_back( new Piece("010\n010\n111"));
     tableauPieces->push_back( new Piece("010\n111\n010"));     
     tableauPieces->push_back( new Piece("1\n11\n011"));
     tableauPieces->push_back( new Piece("11\n0111"));
     tableauPieces->push_back( new Piece("11\n11\n1"));
     tableauPieces->push_back( new Piece("1\n1\n1\n1\n1"));
     tableauPieces->push_back( new Piece("1111\n01"));
     tableauPieces->push_back( new Piece("111\n001\n001"));
     tableauPieces->push_back( new Piece("1111\n0001"));
     tableauPieces->push_back( new Piece("11\n01\n011"));
     tableauPieces->push_back( new Piece("11\n01\n11"));
     // tableauPieces->push_back( new Piece("01\n111\n001"));
     // Avec rotation :
     tableauPieces->push_back( new Piece("011\n11\n01"));
     /*  
	 010
	 111
	 001
	 
	 011
	 110
	 010
     */
     
     cout << "On renomme le tout " << endl;
     tableauPieces->at(0)->rename("a");
     tableauPieces->at(1)->rename("b");
     tableauPieces->at(2)->rename("c");
     tableauPieces->at(3)->rename("d");
     tableauPieces->at(4)->rename("e");
     tableauPieces->at(5)->rename("f");
     tableauPieces->at(6)->rename("g");
     tableauPieces->at(7)->rename("h");
     tableauPieces->at(8)->rename("i");
     tableauPieces->at(9)->rename("j");
     tableauPieces->at(10)->rename("k");
     tableauPieces->at(11)->rename("l");     

     tableauPieces->at(1)->afficher();


     // On vérifie que les pieces et le plateau ont le même nombre de cases:
     int nbCasesPieces = 0;
     for(unsigned int i = 0; i < tableauPieces->size(); i++)
	  nbCasesPieces += tableauPieces->at(i)->getNbCases();
     
     if(nbCasesPieces != plateau2->getNbCases())
     {
	  cout << "impossible à résoudre, pas le même nombre de cases" << endl;
	  exit (EXIT_FAILURE);
     }
     else
     {
	  cout << "Il y a bien le bon nombre de cases" << endl;
     }
	      cout << "On lance la récurrence" << endl;
     
     Plateau *plateauFinal = remplirRecur(plateau2, tableauPieces,0);
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

Plateau *Pentamino::remplirRecur(Plateau *plateau, vector< Piece* > *pieces, int niveau, string chaine)
{
     // cout << "On reccur !" << endl;
     // On cherche la première case vide
     
     int *array = plateau->searchFirstEmptyCase();
     // Si il n'y en a pas, on a remplit tout le tableau, c'est gagné
     if(array[1] == -1)
     {
	  return plateau;
     }
     // Sinon on rajoute une nouvelle piece :
     Plateau *plateauCopy = 0;
     int retourAjout = -1;
     Plateau *retourPlateau = 0;
     // vector< Piece* > *pieces_del = new vector< Piece* >;
     // On parcours toutes les lettres
/*
     if(niveau == 6  && chaine[0] == 'f' && chaine[1] == 'e' && chaine[2] == 'g' && chaine[3] == 'h')
     {
	  cout << chaine << endl;
	  plateau->afficher();
	  cout << endl;
     }
*/   
     for(unsigned int i=0; i < pieces->size(); i++)
     {
	  // cout << "Piece nb " << i << " sur " << pieces->size() << endl;
	  // On essaye d'ajouter cette pièce
	  if(niveau == 0)
	  {
	       pieces->at(i)->afficher();
	       cout << endl;
	  }

	  
	  plateauCopy = new Plateau( *plateau);
	  for(int angle = 0; angle <= 5; angle++)
	  {
	       retourAjout = plateauCopy->addPiece(pieces->at(i)->transform(angle), array[0], array[1]);
	       if(retourAjout > 0)
	       {
		    // Si ça fonctionne on envoie à la fonction courrante le nouveau tableau et les nouvelles pièces (penser à enlever la pièce courante)
		    // pieces_del = pieces;
		    vector< Piece* > pieces_del(*pieces);
		    pieces_del.erase(pieces_del.begin()+i);
		    retourPlateau = remplirRecur(plateauCopy, &pieces_del, niveau + 1, chaine + pieces->at(i)->getName());
		    // Si la fonction retourne un tableau plein, on le retourne
		    // (on a gagné)
		    if(retourPlateau)
		    {
			 // retourPlateau->afficher();
			 return retourPlateau;
		    }
	       }

	  }
	  delete plateauCopy;
	 
     }
     // Si on fini la boucle, on n'a rien trouvé : perdu
     return 0;
}
