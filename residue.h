#ifndef RESIDUE_H
#define RESIDUE_H

#include <iostream>
#include <string>

#include "global.h"

using namespace std;

class Residue
{
public:
    Residue();
    Residue(int argAtomFirst, const string &argResName, int argResNumber);
    
    int getAtomFirst() const;
    int getAtomLast() const;

    void setAtomFirst(const int &argAtomFirst);
    void setAtomLast(const int &argAtomLast);
    
    string getResName() const;
    int getResNumber() const;
    
    void setResName(const string &argResName);
    void setResNumber(const int &argResNumber);
    
    char getResChar() const;
    
    void getColourRgb(int &r, int &g, int &b) const;

    void setPosXY(int j1, int k1);
    int getPosX() const;
    int getPosY() const;
    
    int getAtomsCount() const;
    
private:
    int atomFirst;
    int atomLast;
    string resName;
    int resNumber;
    
    int posX;
    int posY;
};

#endif