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
     void setPlateau(std::string file);
     /* void setPlateau(std::string array[]); */
     void setPlateauString(std::string chaine);
     int addPiece(Piece *piece, int x, int y);
     
     void afficher();

     // get
     std::string getEl(int x, int y);
     int getNbLines();
     int getNbColonnes();
     std::string toString();
     // set
     void setEl(int x, int y, std::string value);

protected:
     std::vector< std::vector<std::string> > *m_tableau;

};

#endif
