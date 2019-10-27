#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFileDialog>

#include "graphicwidget.h"

#include <fstream>
#include <sstream>

#include "global.h"
#include "atom.h"

using namespace std;

void GraphicWidget::openFile()
{
    string strFileName = previous_filename;
    fileName = QFileDialog::getOpenFileName(this, "Open", ".");
    
    if (fileName.isEmpty())
    {
        cout << "Currently still displaying file: \n" << strFileName << endl;
        fileName = previous_QFilename;
        return;
    }
    else
    {
        
        previous_QFilename = fileName;
        
        strFileName = fileName.toLatin1().constData();
        cout << "\n=======================================\nFilename: " << strFileName << endl;
    
        atomsContainer.clear();
        residuesContainer.clear();
    
        readPdbFile(strFileName);
        setResidues();
        update();
        previous_filename = strFileName;
    }
}

void GraphicWidget::hideGraphic()
{
    cout << "'Hide' button was pressed" << endl;
    displayResidueOneLetterCodes = false;
    update();
}

void GraphicWidget::showGraphic()
{
    cout << "'Show' button was pressed" << endl;
    displayResidueOneLetterCodes = true;
    update();
}

void GraphicWidget::mousePressEvent(QMouseEvent *event)
{
    posX = event->x();
    posY = event->y();
    
    update();
    
    cout << "A mouse button was pressed" << endl;
    cout << "Mouse cursor coordinates: ";
    cout << event->x() << ", " << event->y() << endl;
    if (event->button() == Qt::LeftButton)
    {
        cout << "Left ";
    }
    if (event->button() == Qt::MidButton)
    {
        cout << "Middle ";
    }
    if (event->button() == Qt::RightButton)
    {
        cout << "Right ";
    }
    cout << "mouse button was pressed" << endl;
    
    
    if (event->button() == Qt::LeftButton)
    {
        for (int i = 0; i < int (residuesContainer.size()); i++)
        {            
            if ((event->x() >= (residuesContainer[i]->getPosX())) && (event->x() <= ((residuesContainer[i]->getPosX()) + 14)) && (event->y() >= (residuesContainer[i]->getPosY())) && (event->y() <= ((residuesContainer[i]->getPosY()) + 14)))
            {
                selectedResidue = i;
                cout << "Residue number "<< selectedResidue + 1 << " was selected" << endl;
                break;
            }
        }
    }
    
    update();
}

GraphicWidget::GraphicWidget()
{
    displayResidueOneLetterCodes = true;
    fileName = "No file supplied";
}



bool GraphicWidget::readPdbFile(string argInputPdbFileName)
{
    string line = "";
    string recordName = "";
    ifstream ifile;
    Atom *atom = 0;
    ifile.open(argInputPdbFileName.c_str());
    if (ifile.fail())
    {
        cout << "Could not open the input file!11\n";
        return false;
    }
    
    while (!ifile.eof())
    {
        getline(ifile, line);
        if (line.length() >= 6)
        {
            recordName = line.substr(0, 6);
            
            if (recordName == "ATOM  " || recordName == "HETATM")
            {
                atom = new Atom;
                
                atom->readLine(line);
                atomsContainer.push_back(atom);
                atom->print();
            }
        }
    }

    if (error_number != 0)
    {
        cout << "=======================================\n" << "Some lines were not read correctly!\nSequence displaying will be incomplete/incorrect!\nPlease, check the input PDB file\nNumber of error lines: " << error_number << "\n=======================================\nThanks for using the program!\n=======================================" << endl;
    }
    
    else
    {
        cout << "=======================================\n" << "All lines were read successfully!\nThanks for using the program!\n=======================================" << endl;
    }
    
    ifile.close();

    error_number = 0;
    n = 0;
    
    return true;
}

void GraphicWidget::setResidues()
{
    Residue *residue = 0;
    string k = "";
    
    int n = 0;
    int count = 1;
    int aux = 0;
    int q = 0;
    
    for (int i = 0; i < int (atomsContainer.size()); i++)
    {        
        if (i < int (atomsContainer.size() - 1))
        {
            n = i + 1;
        }
        
        if (int (atomsContainer[n]->getResNumber()) > int (atomsContainer[i]->getResNumber()))
        {
            count++;
            
            residue = new Residue;
            residue->setResName(atomsContainer[i]->getResName());
            residue->setResNumber(int (atomsContainer[i]->getResNumber()));
            residue->setAtomFirst(aux);
            residue->setAtomLast(i);
            residuesContainer.push_back(residue);
            aux = i + 1;
            
            //cout << "ResName: " << residuesContainer[q]->getResName() << " | ResNumber: " << int (residuesContainer[q]->getResNumber()) << " | First atom number: " << residuesContainer[q]->getAtomFirst() << " | Last atom number: " << residuesContainer[q]->getAtomLast() << " | Residue symbol: " << residuesContainer[q]->getResChar() << endl;
            q++;
        }
        
        //dealing with the very last atom
        if ((i + 1) == int (atomsContainer.size()))
        {
            count++;
            
            residue = new Residue;
            residue->setResName(atomsContainer[i]->getResName());
            residue->setResNumber(int (atomsContainer[i]->getResNumber()));
            residue->setAtomFirst(aux);
            residue->setAtomLast(i);
            residuesContainer.push_back(residue);
            aux = i + 1;
            
            //cout << "ResName: " << residuesContainer[q]->getResName() << " | ResNumber: " << int (residuesContainer[q]->getResNumber()) << " | First atom number: " << residuesContainer[q]->getAtomFirst() << " | Last atom number: " << residuesContainer[q]->getAtomLast() << " | Residue symbol: " << residuesContainer[q]->getResChar() << endl;
            q++;
        }
        
    }
}

void GraphicWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QFont font_text("Helvetica", 10);
    painter.setPen(QPen((Qt::black), 1));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0, 0, width() - 1, height() - 1);
    
    painter.setFont(font_text);
    painter.setPen(QPen((Qt::black), 1));
    painter.drawText(20, 20, "File:");
    
    painter.drawText(20, 35, fileName);
    
    
    if (int (residuesContainer.size()) != 0)
    {
        QPen pen_text(Qt::black, 1);
        QPen pen_text_white(Qt::white, 1);
        QFont font1("Helvetica", 10);
        
        int k = 0;
        int q = 0;
        for (int i = 0; i <= int (residuesContainer.size()/20); i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (q == int (residuesContainer.size()))
                {
                    break;
                }
                
                residuesContainer[q]->getColourRgb(RColour, GColour, BColour);
                
                QPen pen_box(QColor(RColour, GColour, BColour), 1);
                QBrush brush_box(QColor(RColour, GColour, BColour));
                painter.setPen(pen_box);
                painter.setBrush(brush_box);
                painter.drawRect((j * 14 + 9), (47 + k), 14, 14);
                residuesContainer[q]->setPosXY(j, k);
                
                if (displayResidueOneLetterCodes == true)
                {
                    if (residuesContainer[q]->getResChar() == 'I' || residuesContainer[q]->getResChar() == 'L' || residuesContainer[q]->getResChar() == 'V')
                    {
                        painter.setPen(pen_text_white);
                    }
                    else
                    {
                        painter.setPen(pen_text);
                    }
                    painter.setFont(font1);
                    painter.drawText((11 + j * 14), (59 + k), QString(QChar(residuesContainer[q]->getResChar())));
                }
                
                q++;
            }
            k = k + 25;
        }

        painter.setPen(QPen((Qt::red), 2));
        painter.setBrush(QBrush(Qt::NoBrush));
        painter.drawRect((residuesContainer[selectedResidue]->getPosX()), (residuesContainer[selectedResidue]->getPosY()), 14, 14);
        
        
        painter.setPen(QPen((Qt::black), 2));
        string residueDescription = "";  
        ostringstream ss;    
        ss << "Residue: ";
        ss << residuesContainer[selectedResidue]->getResName();
        ss << residuesContainer[selectedResidue]->getResNumber();
        ss << "     Number of atoms: ";
        ss << residuesContainer[selectedResidue]->getAtomsCount();
        residueDescription = ss.str();    
        if (residueDescription.length() > 0)
        {
            painter.drawText(20, height() - 30, residueDescription.c_str());
        }
    }
}
