#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "atom.h"

#include "global.h"

int n = 0;

Atom::Atom()
{
    recordType = RECORD_UNKNOWN;
    int atomNumber = 0;
    string atomName = "    ";
    char altLocation = ' ';
    string resName = "   ";
    char chainID = ' ';
    int resNumber = 0;
    char iCode = ' ';
    double coordX = 0;
    double coordY = 0;
    double coordZ = 0;
    double occupancy = 0;
    double tempFactor = 0;
    string elName = "  ";
    string formalCharge = "  ";
    bool isOccupancy = false;
    bool isTempFactor = false;
}

void Atom::readLine(const string &line)
{
    n++;
    string recordName;
    string s;
    istringstream sstream;
    
    if (line.length() < 53)
    {
        cout << "The line is too short!11\nLine number (starting from first ATOM record): " << n << endl;
        error_number++;
        return;
    }
    
    recordName = line.substr(0, 6);
    if (recordName == "ATOM  ")
    {
        recordType = RECORD_ATOM;
    }
    else if (recordName == "HETATM")
    {
        recordType = RECORD_HETATM;
    }
    else
    {
        return;
    }
    
    s = line.substr(6, 5);
    sstream.str(s);
    sstream.clear();
    sstream >> atomNumber;
    if (sstream.fail())
    {
        cout << "File reading error!11 (atomNumber)\nLine number (starting from first ATOM record): " << n << endl;
        error_number++;
        return;
    }
    
    atomName = line.substr(12, 4);
    altLocation = line[16];
    resName = line.substr(17, 4);
    chainID = line[21];
    s = line.substr(22, 4);
    sstream.str(s);
    sstream.clear();
    sstream >> resNumber;
    if (sstream.fail())
    {
        cout << "File reading error!11 (resNumber)\nLine number (starting from first ATOM record): " << n << endl;
        error_number++;
        return;
    }
    iCode = line[26];
    
    
    
    
    s = line.substr(30, 24);
    sstream.str(s);
    sstream.clear();
    sstream >> coordX >> coordY >> coordZ;
    if (sstream.fail())
    {
        cout << "File reading error!22 (coordinates)\nLine number (starting from first ATOM record): " << n << endl;
        error_number++;
        return;
    }
    
    if (line.length() >= 60)
    {
        s = line.substr(54, 6);
        sstream.str(s);
        sstream.clear();
        sstream >> occupancy;
        if (!sstream.fail())
        {
            isOccupancy = true;
        }
    }
    
    if (line.length() >= 66)
    {
        s = line.substr(60, 6);
        sstream.str(s);
        sstream.clear();
        sstream >> tempFactor;
        if (!sstream.fail())
        {
            isTempFactor = true;
        }
    }
    
    if (line.length() >= 78)
    {
        elName = line.substr(76, 2);
    }
    
    if (line.length() >= 80)
    {
        formalCharge = line.substr(78, 2);
    }
}

void Atom::writeLine(ofstream &ofile)
{
    if (recordType == RECORD_ATOM)
    {
        ofile << "ATOM  ";
    }
    else if (recordType == RECORD_HETATM)
    {
        ofile << "HETATM";
    }
    else
    {
        return;
    }
    
    ofile << right << setw(5) << atomNumber;
    ofile << ' ';
    ofile << left << setw(4) << atomName;
    ofile << altLocation;
    ofile << left << setw(3) << resName;
    ofile << chainID;
    ofile << right << setw(4) << resNumber;
    ofile << iCode;
    ofile << "   ";
    ofile << right << fixed << setprecision(3);
    ofile << setw(8) << coordX;
    ofile << setw(8) << coordY;
    ofile << setw(8) << coordZ;
    
    if (isOccupancy)
    {
        ofile << right << fixed << setprecision(2) << setw(6) << occupancy;
    }
    else
    {
        ofile << "      ";
    }
    
    if (isTempFactor)
    {
        ofile << right << fixed << setprecision(2) << setw(6) << tempFactor;
    }
    else
    {
        ofile << "      ";
    }
    
    ofile << "          ";
    ofile << right << setw(2) << elName;
    ofile << left << setw(2) << formalCharge;
    ofile << endl;
}
        
void Atom::print()
{
    //cout << atomNumber << " " << atomName << " " << resName << " " << resNumber << " " << coordX << ", " << coordY << ", " << coordZ << " " << elName << endl;
}

string Atom::getResName() const
{
    return resName;
}

int Atom::getResNumber() const
{
    return resNumber;
}

int Atom::getAtomNumber() const
{
    return atomNumber;
}
