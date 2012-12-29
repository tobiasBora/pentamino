#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>

	
class Piece
{
public:
     Piece();
     Piece(std::string chaine);
     Piece(std::vector< std::vector<std::string> > *tableau);
     ~Piece();
     void setPiece(std::string file);
     void setPieceString(std::string chaine);
     void afficher();
     // get
     std::string getEl(int x, int y);
     int getNbLines();
     int getNbColonnes();
     int getNbCases();
     std::string toString();
     std::string getName();
     int *searchFirstEmptyCase();
     // set
     void setEl(int x, int y, std::string value);
     void remplace(std::string avt, std::string apres);
     void rename(std::string apres);

     Piece *transform(int angle);
protected:
     std::vector< std::vector<std::string> > *m_tableau;
     std::string m_name;
};
// d i
#endif

