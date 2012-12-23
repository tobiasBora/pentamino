#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <vector>
#include <string>

	
class Plateau
{
public:
     Plateau();
     void setPlateau(std::string file);
     /* void setPlateau(std::string array[]); */
     void setPlateauString(std::string chaine);
     void afficher();
     void refresh();
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
