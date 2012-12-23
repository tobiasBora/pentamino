#include <iostream>
#include <stdlib.h>
#include "piece.h"
#include "string"
#include <fstream>
#include <vector>
#include <typeinfo>


using namespace std;

Piece::Piece()
{
     cout << "Création de la pièce" << endl;

}

void Piece::setPiece(string fileName)
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
	  m_tableau->clear();

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
	  		 setEl(nbLine,i,"1");	 
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


void Piece::setPieceString(string chaine)
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
		    setEl(line, currentChar, "1");	 
	       }
	       
	       currentChar++;
	  }
     }
     
     
}

void Piece::afficher()
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


// Fonctions get :

string Piece::getEl(int x, int y)
{
     return m_tableau->at(x)[y];
}

int Piece::getNbLines()
{
     return m_tableau->size();
}

int Piece::getNbColonnes()
{
     return m_tableau->at(0).size();
}
// Fonctions set :

void Piece::setEl(int x,int y,std::string value)
{
     m_tableau->at(x)[y] = value;
}

string Piece::toString()
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
