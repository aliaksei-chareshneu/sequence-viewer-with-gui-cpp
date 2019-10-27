#ifndef ATOM_H
#define ATOM_H

#include <iostream>
#include <string>

#include "global.h"

extern int n;

using namespace std;

class Atom
{
public:
    
    
    static const int RECORD_UNKNOWN = 0;
    static const int RECORD_ATOM = 1;
    static const int RECORD_HETATM = 2;

    Atom();

    void readLine(const string &line);
    void writeLine(ofstream &ofile);
    void print();
    string getResName() const;
    int getResNumber() const;
    
    int getAtomNumber() const;

private:
    int recordType;
    int atomNumber;
    string atomName;
    char altLocation;
    string resName;
    char chainID;
    int resNumber;
    char iCode;
    double coordX;
    double coordY;
    double coordZ;
    double occupancy;
    double tempFactor;
    string elName;
    string formalCharge;
    bool isOccupancy;
    bool isTempFactor;
    
    int line_number;
    int error_lines;
};

#endif
