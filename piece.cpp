#include <iostream>
#include <stdlib.h>
#include "piece.h"
#include "string"
#include <fstream>
#include <vector>
#include <typeinfo>

// TODO :
// -> gérer la rotation des pieces

/*
  Si la case vaut 0, c'est une partie vide de la pièce, un trou
  Pour tout autre caractère, c'est une partie de la pièce
 */


using namespace std;

Piece::Piece()
{
     cout << "Création de la pièce" << endl;
     m_tableau = 0;
     m_name = "?";
}

Piece::Piece(string chaine)
{
     setPieceString(chaine);
     m_name = "?";
}

Piece::Piece(std::vector< std::vector<std::string> > *tableau)
{
     m_name = "?";
     m_tableau = new vector< vector<string> >(*tableau);
}

Piece::~Piece()
{
     delete m_tableau;
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
     
     // m_tableau->clear();
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

int Piece::getNbCases()
{
     int lignes = getNbLines();
     int colonnes = getNbColonnes();
     int n = 0;
     for(int i=0; i<lignes;i++)
     {
	  for(int j=0; j<colonnes; j++)
	  {
	       if(getEl(i,j)!="0")
		    n++;
	  }
     }
     return n;
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

string Piece::getName()
{
     return m_name;
}


int *Piece::searchFirstEmptyCase()
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
	       if(getEl(i,j) != "0")
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

void Piece::setEl(int x,int y,std::string value)
{
     m_tableau->at(x)[y] = value;
}

void Piece::remplace(string avt, string apres)
{

     int lignes = getNbLines();
     int colonnes = getNbColonnes();
     for(int i=0; i<lignes;i++)
     {
	  for(int j=0; j<colonnes; j++)
	  {
	       if(getEl(i,j) == avt)
		    setEl(i,j,apres);
	  }
     }
}


void Piece::rename(string apres)
{
     m_name = apres;
     int lignes = getNbLines();
     int colonnes = getNbColonnes();
     for(int i=0; i<lignes;i++)
     {
	  for(int j=0; j<colonnes; j++)
	  {
	       if(getEl(i,j) != "0")
		    setEl(i,j,apres);
	  }
     }

}

Piece *Piece::transform(int angle)
{
     // On fait tourner la piece d'un angle donné :
     // 0 = rien
     // 1 = 90° sens trigo
     // 2 = 180°
     // 3 = 90° sens horaire
     // 4 = symétrie horizontale
     // 5 = symétrie verticale

     if(angle == 0)
     {
	  return this;
     }
     
     int nbLines = getNbLines();
     int nbColonnes = getNbColonnes();
     vector< vector<string> > *tabFinal = new vector< vector<string> >(nbColonnes, vector<string>(nbLines, "0"));
     if(angle == 1 || angle == 3)
	  tabFinal = new vector< vector<string> >(nbColonnes, vector<string>(nbLines, "0"));
     else
	  tabFinal = new vector< vector<string> >(nbLines, vector<string>(nbColonnes, "0"));

     for(int i=0; i < nbLines; i++)
     {
	  for(int j=0; j < nbColonnes; j++)
	  {
	       if(angle == 0)
		    tabFinal->at(i).at(j) = getEl(i,j);
	       else if(angle == 1)
		    tabFinal->at(nbColonnes - j - 1).at(nbLines - i - 1) = getEl(i,j);
	       else if(angle == 2)
		    tabFinal->at(nbLines - i - 1).at(nbColonnes - j - 1) = getEl(i,j);
	       else if(angle == 3)
		    tabFinal->at(j).at(i) = getEl(i,j);
	       else if(angle == 4)
		    tabFinal->at(nbLines - i -1).at(j) = getEl(i,j);
	       else if(angle == 5)
		    tabFinal->at(i).at(nbColonnes - j - 1) = getEl(i,j);

	  }
     }

     return new Piece(tabFinal);
}
