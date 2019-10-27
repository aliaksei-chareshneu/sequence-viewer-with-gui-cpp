#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>

#include <vector>
#include "atom.h"
#include "residue.h"

#include "global.h"

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    GraphicWidget();
    
    bool readPdbFile(string argInputPdbFileName);

    void setResidues();
    
protected:
    virtual void paintEvent (QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent *event);
    
private:
    int posX, posY;
    bool displayResidueOneLetterCodes;
    QString fileName;
    
    vector<Atom*> atomsContainer;
    vector<Residue*> residuesContainer;
    
    int RColour;
    int GColour;
    int BColour;
    
    int selectedResidue;
    
    string previous_filename;
    QString previous_QFilename;
    
private slots:
    void hideGraphic();
    void showGraphic();
    void openFile();
    
};

#endif