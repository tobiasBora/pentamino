#include <iostream>
#include <stdlib.h>
#include "plateau.h"
#include "string"
#include <fstream>
#include <vector>
#include <typeinfo>
#include "piece.h"
/*
  Dans un tableau :
  0 = Case interdite (hors tableau)
  1 = Case vide
  2,3... = Case prise par une autre pièce


*/


using namespace std;

Plateau::Plateau()
{
     cout << "Création du plateau" << endl;

}

// Constructeur de copie :
Plateau::Plateau(Plateau const& plateauACopier)
{
     m_tableau = new vector< vector<string> >(*plateauACopier.m_tableau);
}

void Plateau::setPlateau(string fileName)
{     
     // Pour remplir le plateau avec le contenu d'un fichier
     // 00000000000
     // 00000000000
     // 0000  00000
     // 00000000000
     // 00000000000

     
     ifstream fichier(fileName.c_str(), ios::in);
     char caractere;
     string ligne;
     if (fichier)
     {
	  
// while getline(file, varstring)
	  int maxChar = 0;
	  int size = 0;
	  int nbLine = 0;
	  while(getline(fichier, ligne))
	  {
	       size = ligne.size();
	       if(size > maxChar)
		    maxChar = size;
	       nbLine++;
	  }

	  // On revient en début de fichier, et on néttoie le tag "eof" :
	  fichier.clear();
	  fichier.seekg(0);

	  // On vide le tableau pour le remplir à 0
	  // m_tableau->clear();

	  m_tableau = new vector< vector<string> >(nbLine, vector<string>(maxChar, "0"));

	  nbLine = 0;
	  // On remplit le tableau avec le contenu du fichier
	  while(getline(fichier, ligne))
	  {
	       for(unsigned int i = 0; i < ligne.size(); i++)
	       {
	  	    caractere = ligne[i];
		    if(caractere == ' ' || caractere == '0')
	  	    {
	  		 // Les espaces et 0 sont considérés comme des cases interdites
	  		 setEl(nbLine,i, "0");
	  	    }
	  	    else
	  	    {
	  		 // Les 1 ou les autres caractères sont interdits
	  		 // setEl(nbLine,i,"1");
			 setEl(nbLine, i, &caractere);
	  	    }
	       }

	       nbLine ++;
	  }

	  fichier.close();
     }
     else
     {
	  cerr << "impossible d'ouvrir le fichier";

     }
	       
     
}


void Plateau::setPlateauString(string chaine)
{
     unsigned int maxChar = 0;
     unsigned int currentChar = 0;
     char caractere;
     unsigned int nbLines = 0;
     caractere = ' ';
     
     for(unsigned int i=0; i < chaine.size(); i++)
     {
	  
	  caractere = chaine[i];
	  if(caractere == '\n')
	  {
	       if(currentChar > maxChar)
	       {
		    maxChar = currentChar;
	       }
	       currentChar = 0;
	       nbLines++;
	  }
	  else
	  {
	       currentChar++;
	  }
     }
     // Si la dernière ligne n'est pas vide :
     if(caractere != '\n')
     {
	  if(currentChar > maxChar)
	  {
	       maxChar = currentChar;
	  }
	  currentChar = 0;
	  nbLines++;
     }
     
     
     m_tableau->clear();
     m_tableau = new vector< vector<string> >(nbLines, vector<string>(maxChar, "0"));
     
     
     int line = 0;
     currentChar = 0;
     
     for(unsigned int i=0; i < chaine.size(); i++)
     {
	  
	  caractere = chaine[i];
	  if(caractere == '\n')
	  {
	       if(currentChar > maxChar)
	       {
		    maxChar = currentChar;
	       }
	       currentChar = 0;
	       line++;
	  }
	  else
	  {
	       if(caractere == ' ' || caractere == '0')
	       {
		    // Les espaces et 0 sont considérés comme des cases interdites
		    setEl(line,currentChar, "0");
	       }
	       else
	       {
		    // Les 1 ou les autres caractères sont interdits
		    // setEl(line, currentChar, "1");
		    setEl(line, currentChar, &caractere);
	       }
	       
	       currentChar++;
	  }
     }
     
     
}

int Plateau::addPiece(Piece *piece, int x, int y)
{
     // On retourne -1 si la piece dépasse le tableau
     // On retourne -2 si la piece chevauche une autre pièce ou une case interdite
     // Sinon retourne 1 (aucun problème)

     // On vérifie qu'on peut le faire au niveau de la place
     if( getNbLines() < x + piece->getNbLines()
	|| getNbColonnes() < y + piece->getNbColonnes())
     {
	  return -1;
     }
     else
     {
	  // Si a première vue on ne dépasse pas
	  // On vérifie qu'un peut le faire sans placer
	  // la pière dans un endroit interdit
	  int nbLines = piece->getNbLines();
	  int nbColonnes = piece->getNbColonnes();
	  for(int i = 0; i < nbLines; i++)
	  {
	       for(int j = 0; j < nbColonnes; j++)
	       {
		    // Si la piece chevauche une case non autorisée
		    if(piece->getEl(i,j) != "0" && getEl(i+x,j+y) != "1")
		    {
			 return -2;
		    }
	       }

	  }
	  // Si on n'a pas eu de problème on remplit
	  string caractere;
	  for(int i=0; i < nbLines; i++)
	  {
	       for(int j=0; j < nbColonnes; j++)
	       {
		    caractere = piece->getEl(i,j);
		    // Si la case de la piece est non vide
		    if(caractere != "0")
		    {
			 setEl(i+x,j+y,caractere);
		    }
	       }

	  }
	  return 1;
	  
     }

}

void Plateau::afficher()
{
     string Case;
     for(int i = 0; i < getNbLines(); i++)
     {
	  cout << "|";
	  for(int j = 0; j < getNbColonnes(); j++)
	  {
	       
	       Case = getEl(i,j);
	       if(Case == "0")
		    cout << " ";
	       else
		    cout << Case;
	  }
	  cout << "|";
	  cout << endl;
     }
}

int Plateau::check(int what)
{
     // -------- Entrée ---------
     // what :
     // 0 (valeur par défaut) = vérifie juste si le tableau est remplit.

     
     // ------- Sortie ----------
     // Cette fonction vérifie l'état du plateau :
     // 0 = rien à signaler
     // 1 = Il ne reste plus aucune case non remplie par 1.
     // -10 = Erreur dans l'execution
     // TODO :
     // -1 = il n'y a aucun bloc fermé de plus de "what" caractères (si what > 0)

     if(what == 0)
     {
	  int lines = getNbLines();
	  int colonnes = getNbColonnes();
	  
	  // On vérifie si il n'est pas remplit :
	  for(int i=0; i<lines; i++)
	  {
	       for(int j=0; j<colonnes; j++)
	       {
		    if(getEl(i,j) == "1")
		    {
			 return 0;
		    }
	       }
	  }
     
	  return 1;
     }

     return -10;
}


// Fonctions get :

string Plateau::getEl(int x, int y)
{
     return m_tableau->at(x)[y];
}

int Plateau::getNbLines()
{
     return m_tableau->size();
}

int Plateau::getNbColonnes()
{
     return m_tableau->at(0).size();
}

int *Plateau::searchFirstEmptyCase()
{
     // Retourne un tableau de deux cases :
     int lines = getNbLines();
     int colonnes = getNbColonnes();
     int *array= new int[2];

     array[0]=-1;
     array[1]=-1;
     
     // On vérifie si il n'est pas remplit :
     for(int i=0; i<lines; i++)
     {
	  for(int j=0; j<colonnes; j++)
	  {
	       if(getEl(i,j) == "1")
	       {
		    array[0]=i;
		    array[1]=j;
		    return array;
	       }
	  }
     }

     return array;
}

// Fonctions set :

void Plateau::setEl(int x,int y,std::string value)
{
     m_tableau->at(x)[y] = value;
}

string Plateau::toString()
{
     string chaine("");
     for(int i = 0; i < getNbLines(); i++)
     {
	  for(int j = 0; j < getNbColonnes(); j++)
	  {
	       
	       chaine += getEl(i,j);
	  }
	  chaine += "\n";
     }
     return chaine;
}
