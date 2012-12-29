#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <vector>
#include <string>
#include "piece.h"
	
class Plateau
{
public:
     Plateau();
     // Constructeur de copie :
     Plateau(Plateau const& plateauACopier);
     // Destructeur :
     ~Plateau();
     void setPlateau(std::string file);
     /* void setPlateau(std::string array[]); */
     void setPlateauString(std::string chaine);
     int addPiece(Piece *piece, int x, int y);
     void afficher();
     int check(int what=0);

     // get
     std::string getEl(int x, int y);
     int getNbLines();
     int getNbColonnes();
     int getNbCases();
     std::string toString();
     int *searchFirstEmptyCase();
     // set
     void setEl(int x, int y, std::string value);

protected:
     std::vector< std::vector<std::string> > *m_tableau;

};

#endif
