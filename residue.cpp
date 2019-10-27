#include <fstream>
#include <sstream>
#include <iomanip>

#include "residue.h"
#include "atom.h"

#include "global.h"

Residue::Residue()
{
    int atomFirst = 0;
    int atomLast = 0;
    string resName = "   ";
    int resNumber = 0;
}

Residue::Residue(int argAtomFirst, const string &argResName, int argResNumber)
{
    int atomFirst = argAtomFirst;

    string resName = argResName;
    int resNumber = argResNumber;
}

int Residue::getAtomFirst() const
{
    return atomFirst;
}

int Residue::getAtomLast() const
{
    return atomLast;
}

void Residue::setAtomFirst(const int &argAtomFirst)
{
    atomFirst = argAtomFirst;
}

void Residue::setAtomLast(const int &argAtomLast)
{
    atomLast = argAtomLast;
}

string Residue::getResName() const
{
    return resName;
}

int Residue::getResNumber() const
{
    return resNumber;
}

void Residue::setResName(const string &argResName)
{
    resName = argResName;
}

void Residue::setResNumber(const int &argResNumber)
{
    resNumber = argResNumber;
}

char Residue::getResChar() const
{
    if (resName == "ALA ")
        return 'A';
    else if (resName == "ARG ")
        return 'R';
    else if (resName == "ASN ")
        return 'N';
    else if (resName == "ASP ")
        return 'D';
    else if (resName == "CYS ")
        return 'C';
    else if (resName == "GLN ")
        return 'Q';
    else if (resName == "GLU ")
        return 'E';
    else if (resName == "GLY ")
        return 'G';
    else if (resName == "HIS ")
        return 'H';
    else if (resName == "ILE ")
        return 'I';
    else if (resName == "LEU ")
        return 'L';
    else if (resName == "LYS ")
        return 'K';
    else if (resName == "MET ")
        return 'M';
    else if (resName == "PHE ")
        return 'F';
    else if (resName == "PRO ")
        return 'P';
    else if (resName == "SER ")
        return 'S';
    else if (resName == "THR ")
        return 'T';
    else if (resName == "TRP ")
        return 'W';
    else if (resName == "TYR ")
        return 'Y';
    else if (resName == "VAL ")
        return 'V';
    else
        return 'X';

}

void Residue::getColourRgb(int &r, int &g, int &b) const
{
    if (resName == "ALA ")
        { r = 204; g = 255; b = 255; }
    else if (resName == "ARG ")
        { r = 230; g = 6; b = 6; }
    else if (resName == "ASN ")
        { r = 255; g = 153; b = 0; }
    else if (resName == "ASP ")
        { r = 255; g = 204; b = 153; }
    else if (resName == "CYS ")
        { r = 0; g = 255; b = 255; }
    else if (resName == "GLN ")
        { r = 255; g = 102; b = 0; }
    else if (resName == "GLU ")
        { r = 255; g = 204; b = 0; }
    else if (resName == "GLY ")
        { r = 0; g = 255; b = 0; }
    else if (resName == "HIS ")
        { r = 255; g = 255; b = 153; }
    else if (resName == "ILE ")
        { r = 0; g = 0; b = 128; }
    else if (resName == "LEU ")
        { r = 51; g = 102; b = 255; }
    else if (resName == "LYS ")
        { r = 198; g = 6; b = 0; }
    else if (resName == "MET ")
        { r = 153; g = 204; b = 255; }
    else if (resName == "PHE ")
        { r = 0; g = 204; b = 255; }
    else if (resName == "PRO ")
        { r = 255; g = 255; b = 0; }
    else if (resName == "SER ")
        { r = 204; g = 255; b = 153; }
    else if (resName == "THR ")
        { r = 0; g = 255; b = 153; }
    else if (resName == "TRP ")
        { r = 204; g = 153; b = 255; }
    else if (resName == "TYR ")
        { r = 204; g = 255; b = 204; }
    else if (resName == "VAL ")
        { r = 0; g = 0; b = 255; }
    else
        { r = 153; g = 153; b = 153; }
}

void Residue::setPosXY(int j1, int k1)
{
    posX = j1 * 14 + 9;
    posY = 47 + k1;
}

int Residue::getPosX() const
{
    return posX;
}

int Residue::getPosY() const
{
    return posY;
}

int Residue::getAtomsCount() const
{
    return (atomLast - atomFirst + 1);
}