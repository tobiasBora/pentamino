#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>

	
class Piece
{
public:
     Piece();
     void setPiece(std::string file);
     void setPieceString(std::string chaine);
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

